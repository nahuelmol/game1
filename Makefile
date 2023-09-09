OUT = out/out
RESOBJ = res/out/resou.obj
RESRC = res/src/resou.rc

LIBS = -lgdi32

clean:
	g++ cleaner.cpp

pruebaexe:
	pruebas/out

pruebaobjs:
	g++ -I $(CURDIR) -o pruebas/out cleaner.cpp

rs:
	windres -i $(RESRC) -o res/out/resou.res
	windres -i res/out/resou.res -o res/out/resou.obj

compile:
	g++ -I $(CURDIR) -o $(OUT) start.cpp $(LIBS)

run: 
	out/out.exe

exec:
	g++ -I $(CURDIR) -o $(OUT) start.cpp $(LIBS)
	out/out.exe