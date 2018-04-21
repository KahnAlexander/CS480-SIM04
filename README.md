# CS480-SIM04

TODOS
    Build queue for interrupts
    Implement SRTF, FCFS-P, RR-P
    Figure out timer concurrency


NOTES
	using proggen, use 50% run cycle time
	Need to show when config and md files are loading/loaded
	Threads not required for this assignment. Keep anyway? Not sure, probably not.
		Fork for running timer.
			pid = fork();
			if pid = 0
				runTimer(time);

		Run child on timer, when done, join back with parent.
	remember to decrement run cycles for each quantum time

	for FCFS P, if a process hits quantum, it should continue executing if not interrupted. Don't just take next like RR P.
	process time should also be recalculated. Can use hard cycle time value, not realistic time.

	Say Proc2 has 2 cycles to do, with quantum = 3. It will run for 2, and get next opcode for the third, not just end after 2. Then move onto next process.

	Look into annotations? Want that? or not final? No, don't have for final turnin.
	Should be able to handle CPU Idle if every P is blocked.


MORE NOTES
	Loop to end of system data
		-get the correct process (choose based on schedule alg)
		-get correct opCode (easy, just move process's opCode pointer as they are completed)
		-test mode
			-check for 'I'
				-if 'I', load timer with data (probably by fork), then run it
				-set process to Blocked
			-check for 'O'
				-if 'O', load timer with data (probably by fork), then run it
				-set process to Blocked
			-check for 'M'
				-run MMU
				-potential seg fault of process (Why?)
			-check for 'P'
				-calculate one cycle
				-loop up to num cycles or quantum (min of these two)
					-timer
					-at end of loop, check for interrupt
					-if no interrupt, do another cycle
					-if interrupt, move context back to process manager

		-(inside master loop) check for interrupt, resolve.


TIMER
	-takes in a time, pid, desc text, opCode command
	-spin



NOTES WITH STEPHEN
	If IO op found,
		create master struct
		create thread and pass in master struct, detach right after creation
		within thread
			fork process
				child runs timer here
				child exits
				parent does waitpid(pid, NULL, 0) // this waits for the specific child process
				like

						pid_t pid;
						pid = fork()
						if pid=0, do child stuff ,
						else do parent stuff

				once wait is done, mutex lock

				add data to master struct
					log file line
					interrupt node should be last thing to do before freeing/nulling
				null out pointers in master struct
				free master struct
				unlock mutex

			pthread_exit
	If P
		start cycle
		after cycle
			check if quantum time done
				exit opCode
			decrement cycles
			check for interrupt
				put p in Ready
				process interrupt, put that pcb in Ready
	If M
		attempt allocation, access like normal
		at end of opCode, check for interrupts

FCFS-P

	All PCBs in Ready
