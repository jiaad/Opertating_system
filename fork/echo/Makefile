run:
	rm -rf *.o cs_echo a.out && \
	gcc echo.c -o cs_echo && gcc -c parseline.c && gcc prog.c parseline.o -o prog && ./prog && \
	rm -rf *.o cs_echo a.out
clean: 
	rm -rf *.o cs_echo a.out prog
