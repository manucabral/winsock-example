
ifeq (run, $(firstword $(MAKECMDGOALS)))
  address := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(address):;@true)
endif

windows_client: windows_client.c
	gcc windows_client.c -lws2_32 -o windows_client

run_client:
	./windows_client $(address)