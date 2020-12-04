# Data_Visualization_for_Hangzhou-Metro-Traffic
Design a helpful GUI for data visualization of Hangzhou Metro Traffic. ( Language: QT) 
## Introduction
The subway is ahead of other cities' public transportation methods in terms of green,
environmental protection and traffic volume, and has become a priority transportation
mode for major cities. There is a surge in urban metro traffic in China in the past couple
years, but with the new lines being put into operation and the expanding of the network
scale, the problems are also emerging. It’s unsafe and inconvenient for the children and
elderly people to take the subway in rush hours, and numerous subway stations keep
outsiders from knowing how to arrive their destinations. In order to solve the problems
we’ve mention about, I design a Graphic User Interface to help users have a better
understanding of subway inflow and outflow trend, and help outsiders plan feasible routes
to their destination.
## My work
* 1.  Firstly, I implement an initialization interface for users to select the dataset they want
this program to display and select the adjacency matrix of the stations. File dialogs are used
to help users select their csv files.
* 2.  Then I design a main interface to guide users to the parts they want to use. It gives
users four choices, which includes selecting data part, flow view part, plan path part and the
reselect dataset part. StackWidget is used to realize the function of page change.
* 3.  To let users select their interested fields of the dataset, a data filter interface is
designed to help them select. After they make sure the fields they are interested in, they can
go back to the main interface to use the other parts. Lazy evaluation is used to minimize the
unnecessary loading.
* 4.  After that users can choose the flow view part to see the trend of traffic inflow and
outflow over time. They can tune the date, station, start time, end time, time step
parameters to see their interested parts. Amortization is used to amortize the expected
calculation cost. Interpolation will be used to smooth the trend line when only a few points
are available.
* 5.  Finally, plan path part is designed to enable users quickly acquire a feasible route to
their destinations. Transfer cost is taken into consideration while planning the path.
Combining all the mentioned parts, a convenient, good user experienced GUI is
created. 
## Display results
In the end, according to the peak hour factors: occurrence time of peak, peak hour
span and comparison of morning and evening peak traffic, I divided these 81 stations into
three types. Each station type has its own characteristics that can be clearly seen from the
graph view.
