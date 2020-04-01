Source: 

statsmage.com/zorro-on-steroids-ii-data-conversion/

0) Download Dukascopy data using StrategyQuant Tick Downloader	
    
    http://www.strategyquant.com/tickdownloader/
1) Copy ConvertData.c to Zorro/Strategy folder
2) asset being converted has to be defined in AssetsFix.csv file	
3) set the basePath variable to your tick data path	
4) In convert.py script you have to set zorro_path variable
5) Call "python convert.py [tick_data_directory]"	will produce both T1 and T6 data from all files in the directory
