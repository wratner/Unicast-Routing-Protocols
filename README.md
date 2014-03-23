README

Partners:
William Ratner (wratner2)
Scott Tanaka (smtanak2)

Our code is NOT COMPLETE.  We can do the following tasks:

1.) Compile code with no errors
2.) Run manager.c
3.) Parse the topology file and message file
4.) Run distvec.c (our distance vector file)
5.) Connect to the manager
6.) Receive a message from the manager

TO RUN THE CODE:

1.) Make the code by typing "make"
2.) Run the manager file by typing: ./manager TOPOLOGYFILE MESSAGEFILE
	***The manager will print out the topology and the messages.  We do this to show that we parse
	the data correctly***
3.) The manager will now wait for connections from nodes
4.) Run the distance vector protocol by running ./distvec HOSTNAME
5.) The manager will connect to the distvec client, attempt to send the topology, then segfault.  This
	is the extent of our code.
	
Questions about grading/running the code should be directed to:

Scott Tanaka (smtanak2@illinois.edu)
OR
William Ratner (wratner2@illinois.edu)
