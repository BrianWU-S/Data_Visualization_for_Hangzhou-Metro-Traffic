Instructions to run the GUI:
Step1:
Just click build on your QT,and you will see the information interface.
Step2:
Click "Select Dataset " , you can select the dataset. It should be a file folder.
Step3:
Click "Select Adajacency ", you can select the adjacency matrix. It should be a .csv file
Step4:
Now you should be able to see the main interface. Click "select data" and you can go to the data filter interface.
You can choose your interested fields of the dataset by selecting the checkboxes. After you have determined your
choice, click "OK" below. If you don't want to save the changes, click"Cancel" and it will revert to your previous choice.
Attention! If you want to use the FLOW VIEW part to see the graph, you should at least choose Time,StationID, Status. 
Otherwise the GUI will not have enough information to form the graph.  
If yo choose the "LineID", the information about each lines will be displayed in the Plan Path part. Otherwise you will 
only see the route in the Plan Path part. The LineID is irrelevant to the FLOW VIEW  part.
Step4:
Click "Flow View " in the main interface. And you can tune the parameters in the Flow View interface. After you have chosen,
click "OK" and it will take 4-5 seconds for the GUI to form the plot for the first time. After that if you just change the parameters 
of the same date, the GUI will form the graph quickly. Otherwise, change the date will take 4-5 seconds for the GUI to read the 
data of different date.
If the points are less than 6, Interpolation will be used automatically. If you want to see that, just tune the starttime, endtime,timestep
and makes the total points are less than 6.
Step5:
Click"Plan Path" in the main interface to go to the Plan Path interface. Input start stationID and end stationID in the edit boxes. After
that , click OK below and you can see a feasible path displayed below.

PS:
Considering the robustness of the GUI :
If you make mistakes to have the wrong input, you will see the WarningDialog and it will indicate how to rectify your error.
When you see the error dialog, just click OK.  


