# Tool for creating easy to analyze Delta Kossel bed distortion "heat maps"

This simple tool allows you to measure the entire surface of the Delta 3D printer bed and plot the measurements. 

As the result you'd get a nifty chart that visualizes the flatness of the bed - so you can improve it more easily.

!(Sample)[https://github.com/Bougakov/Micromake-D1-3D-printer/raw/master/visualize/Sample%20heat%20map%20chart.png]

How to use this tool:

  1. Save HTML file to your computer. Edit it if needed (for example, change diameter from 170 to something smaller and adjust z-probe height). Open it and check generated G-code. 
  2. Paste code to Repetier and execute. 
  3. Copy resulting log to Excel. Clean it up (use "Text to columns" feature) and save as CSV file with only 3 columns of numbers. 
  4. Open Python script, edit it, if necessary and run it. Chart will be generated automatically. 
  
Discussion: https://www.facebook.com/groups/173676226330714/permalink/391368247894843/?match=dmlzdWFs
