#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>         /* printf */
#include <sys/prctl.h>     /* prctl */
#include <seccomp.h>
#include <string.h>



int main(int argc, char* argv[], char *envp[])
{
  if (argc <= 1) return -1;

	prctl(PR_SET_NO_NEW_PRIVS, 1);
	prctl(PR_SET_DUMPABLE, 0); // ptrace on this process / childs is not allowed
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_ALLOW); // whitelist everything
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clone), 0); // blacklist
	seccomp_load(ctx);
	

	
  char* cmd = argv[1];
  for (int i = 1; i < argc; ++i) argv[i-1] = argv[i];
  argv[argc-1] = 0;

  
	
		



  execvpe(cmd,argv,envp);
	
 
  return 0; 

}
