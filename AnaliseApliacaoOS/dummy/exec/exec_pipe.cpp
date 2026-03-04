// trying to reproduce the pipe behaviour
// ping -c 5 google.com | grep rtt
// | is the same of the pipe() func 
// creating a channel using file descriptor with one end reading and other writing

// The main idea is for the main program create the two processes to exec grp and ping 
// and create the pipe for them.

