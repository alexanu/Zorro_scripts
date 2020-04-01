import re
import os
import sys
import ast
import math
from subprocess import call
from datetime import datetime
from datetime import timedelta

# DEFAULT SETTINGS
data_path = '/cygdrive/c/data/'
zorro_path = '/cygdrive/c/Zorro/'
majors = ['AUD','CAD','CHF','EUR','GBP','JPY','NZD','USD']
period = [0, 1]
shift = 0
price_to_use = 'ask' # price type

# CLASSES
class Tick:
	def __init__(self, time, bid, ask):
		self.time = time
		self.bid = bid
		self.ask = ask

	def mean_price(self):
		return (self.ask + self.bid) / 2

	def spread(self):
		return self.ask - self.bid

	def price(self, price_to_use):
		if price_to_use == 'ask':
			return self.ask
		elif price_to_use == 'bid':
			return self.bid
		elif price_to_use == 'mean':
			return self.mean_price()

	def to_string(self):
		return '{:%Y.%m.%d %H:%M:%S.%f},{:.5f},{:.5f}\n'.format(self.time, \
			self.bid, self.ask)

class Candle:
	op_spread = -1
	cl_spread = -1
	def __init__(self, tick, price_to_use):
		self.time = datetime.strptime(tick.time.strftime('%Y.%m.%d %H:%M'),\
		 '%Y.%m.%d %H:%M')
		self.op = tick.price(price_to_use)
		self.hi = tick.price(price_to_use)
		self.lo = tick.price(price_to_use)
		self.cl = tick.price(price_to_use)
		self.op_spread = tick.spread()
		self.cl_spread = tick.spread()
		self.price_to_use = price_to_use

	def set_op(self, tick):
		self.op = tick.price(self.price_to_use)
		self.op_spread = tick.spread()

	def set_hi(self, tick):
		self.hi = tick.price(self.price_to_use)

	def set_lo(self, tick):
		self.lo = tick.price(self.price_to_use)

	def set_cl(self, tick):
		self.cl = tick.price(self.price_to_use)
		self.cl_spread = tick.spread()

	def to_string(self):
		return '{0},{1:.5f},{2:.5f},{3:.5f},{4:.5f},{5:.5f}\n'.format(
			self.time.strftime('%Y.%m.%d %H:%M'), self.op, self.hi, self.lo,\
			 self.cl, self.cl_spread)

def _read_reverse_char(file_name):
	"""Reads a file backwards char by char, yields whole lines"""
	with open(file_name) as qfile:
		qfile.seek(0, os.SEEK_END)
		position = qfile.tell()
		line = ''
		while position >= 0:
			qfile.seek(position)
			next_char = qfile.read(1)
			if next_char == "\n":
				yield line[::-1]
				line = ''
			else:
				line += next_char
			position -= 1
		yield line[::-1]

def _read_reverse_line(file_name):
	"""Reads a file forward, stores endline positions, then reads 
	the file backwards line by line.
	"""
	with open(file_name, 'r') as fo:
	    line = fo.readline()
	    positions = [0]
	    while line:
	        positions += [fo.tell()]
	        line = fo.readline()

	    positions.reverse()
	    for pos in positions:
	        fo.seek(pos)
	        l = fo.readline()
	        if l and l != '':
	            yield l.strip()

def _read_reverse_tac(file_path):
	"""Reverses file lines and reads the resulting file line by line"""
	in_dir = os.path.dirname(file_path)
	in_fname = os.path.basename(file_path)
	out_fname = re.sub('_tick[\.a-zA-Z]*', '_reversed.tmp', in_fname)
	out_path = os.path.join(in_dir, out_fname)
	# If the reversed file doesn't exist or has a wrong size, create it
	if not os.path.isfile(out_path):
		print 'Reversing file lines...'
		_reverse_file_lines(file_path, out_path)
	if os.path.isfile(out_path):
		in_info = os.stat(file_path)
		out_info = os.stat(out_path)
		if in_info.st_size != out_info.st_size:
			print 'Existing reversed file has a wrong size, recreating...'
			call(['rm', out_path])
			_reverse_file_lines(file_path, out_path)

	with open(out_path, 'r') as fo:
	    line = fo.readline()
	    yield line
	    while line:
	    	line = fo.readline()
	    	yield line

def _reverse_file_lines(input_path, output_path):
	"""Reverses lines in a given file."""
	assert os.path.isfile(input_path) , 'File does not exist'
	reversed_file = open(output_path, 'w')
	call(['tac', os.path.join(input_path)], stdout=reversed_file)
	reversed_file.close()

def split_file(file_name, asset, period, shift=0, price_to_use='ask'):
	"""Split input file and return a list of resulting file paths.

	Keyword arguments:
	file_name -- input file path
	period -- periodicity of resulting data in minutes (0 = tick)
	shift -- number of minutes for timestamp shift
	price_to_use -- price to use for creation of the OHLC data
	"""
	assert os.path.isfile(file_name) , 'File does not exist'
	result_files = []
	f_out = None
	written = True
	prev_t = Tick(datetime(1, 1, 1), 0, 0)
	dt = datetime(1, 1, 1)
	in_dir = os.path.dirname(file_name)
	in_fname = os.path.basename(file_name)
	# Add 1 minute to correct for Zorro's delayed entries
	if period >= 1:
		shift = shift + 1

	for line in _read_reverse_tac(file_name):
		if line.strip() == '':
			continue
		# DUKAS format: 2010.01.03 17:00:00.123,1.43010,1.43040,20.12,28.73
		line_arr = line.rstrip('\n').split(',')
		try:
			dt = datetime.strptime(line_arr[0], '%Y.%m.%d %H:%M:%S.%f') + \
			timedelta(minutes=shift)
		except:
			print('Error parsing line: ', line)
		t = Tick(dt, float(line_arr[1]), float(line_arr[2]))
		
		# On init run and during the file split
		if t.time.year != prev_t.time.year:
			if f_out:
				f_out.close()
			out_fname = asset + '_' + str(t.time.year) + '.csv'
			print(os.path.join(in_dir, out_fname))
			f_out = open(os.path.join(in_dir, out_fname), 'w')
			result_files += [f_out.name]
			try:
				c = Candle(t, price_to_use)
			except:
				print('Error parsing line: ', line)

		prev_t = t

		# Skip the rest as we don't need the candles
		if period == 0:
			f_out.write(t.to_string())
			continue

		written = False
		if t.time < c.time:
			f_out.write(c.to_string())
			written = True
			c = Candle(t, price_to_use)

		# Update OHL prices:
		c.set_op(t)

		if t.price(price_to_use) > c.hi:
			c.set_hi(t)
		elif t.price(price_to_use) < c.lo:
			c.set_lo(t)

	if f_out:
		if not written:
			f_out.write(c.to_string())
			f_out.close()

	return result_files

def get_matching_files(path, pattern):
	"""Return list of files matching given pattern."""
	assert os.path.isdir(path), 'Is not valid directory'
	file_list = []
	if isinstance(pattern, basestring):
		pattern = re.compile(pattern)
	for file in os.listdir(path):
		if pattern.match(file):
			file_list += [os.path.join(path, file)]
	return file_list

def _convert_using_zorro(zorro_path, asset, start, end, period):
	"""Calls Zorro conversuib scripts for given asset, date range and period"""
	asset_name = asset
	zorro_call = ''
	if len(asset) == 6 and (asset[0:3] in majors or asset[3:6] in majors):
		asset_name = asset[0:3] + '/' + asset[3:6]
	if period == 0:
		zorro_call = '{} ConvertData -run -i {} -i {} -a {} -d TCK'.format(
			os.path.join(zorro_path, 'Zorro.exe'), start, end, asset_name)
	else:
		zorro_call = '{} ConvertData -run -i {} -i {} -a {}'.format(
			os.path.join(zorro_path, 'Zorro.exe'), start, end, asset_name)	
	print zorro_call
	os.system(zorro_call)

def convert_file(file_path, zorro_path, period, shift, price_to_use):
	"""Converts a single file"""
	assert os.path.isfile(file_path) , 'File does not exist'
	zorro_exe_path = os.path.join(zorro_path, 'Zorro.exe')
	assert os.path.isfile(zorro_exe_path) , 'Wrong Zorro path'
	file_name = os.path.split(file_path)[1]
	asset = re.sub('_tick\.csv', '', file_name)
	for p in period:
		split_files = split_file(file_path, asset, p, shift, price_to_use)
		start = 0
		end = 0
		for path in split_files:
			f_name = os.path.split(path)[1]
			m = re.search(re.compile('_[0-9]+'), f_name)
			if m:
				year = int(re.sub('_', '', m.group(0)))
				if year < start or start == 0:
					start = year
				if year > end:
					end = year
		_convert_using_zorro(zorro_path, asset, start, end, p)
		for path in split_files:
			call(['rm', path])
	call(['rm', re.sub('_tick\.csv', '_reversed.tmp', file_path)])

def convert_all_files_in_dir(data_path, zorro_path, period, shift, price_to_use):
	"""Converts all files in a directory which are named: [SYMBOL]_tick.csv"""
	assert os.path.isdir(data_path), 'Directory does not exist'
	assert os.path.isfile(os.path.join(zorro_path, 'Zorro.exe')) , \
	'Wrong Zorro directory'
	file_paths = get_matching_files(data_path, '[a-zA-Z0-9]+_tick\.csv')
	for path in file_paths:
		print path
		convert_file(path, zorro_path, period, shift, price_to_use)

def show_help():
	print 'Usage: python convert.py [OPTIONS] [FILE]'
	print '\nList of options:'
	print '-p=MINUTES\tPeriod of resulting candles in minutes (0 produces tick data).'
	print '\t\tSeveral values separated by commas can be used, e.g. \'0,1\''
	print '\t\tActually only 0 or 1 work at the moment:P'
	print '-s=MINUTES\tNumber of minutes to shift the data (negative numbers possible)'
	print '-a | -b | -m\tUse ask | bid | mean price for candle computation'
	print '\nDefault values: python convert.py -p=\'0,1\' -s=0 -a /cygdrive/e/tickdata/'
	sys.exit()

# If the file is run as a script:
if __name__ == '__main__':
	for arg in sys.argv:
		try:
			if arg.startswith('-h'):
				show_help()
			elif arg.startswith('-p'):
				period = map(int, [a.strip() for a in arg[3:].split(',')])
				#period = int(arg[3:])
			elif arg.startswith('-s'):
				shift = int(arg[3:])
			elif arg.startswith('-a'):
				price_to_use = 'ask'
			elif arg.startswith('-b'):
				price_to_use = 'bid'
			elif arg.startswith('-m'):
				price_to_use = 'mean'
			elif arg != sys.argv[0]:
				print 'Unrecognized argument: {}'.format(arg)
		except Exception as inst:
			print type(inst) 
			print inst.args
			print inst
			show_help()
	print 'Period: {}, Time shift: {}, Price to use: {}'.format(
		period, shift, price_to_use)
	
	in_path = ''
	if sys.argv[0] != sys.argv[len(sys.argv)-1]:
		in_path = sys.argv[len(sys.argv)-1]

	# Call data conversion method based on argument type
	if os.path.isfile(in_path):
		convert_file(in_path, zorro_path, period, shift, price_to_use)
	elif os.path.isdir(in_path):
		convert_all_files_in_dir(
			in_path, zorro_path, period, shift, price_to_use)
	elif os.path.isdir(data_path):
		convert_all_files_in_dir(
			data_path, zorro_path, period, shift, price_to_use)
	else:
		print in_path + 'in_path is not a valid file or directory'
		sys.exit(1)
