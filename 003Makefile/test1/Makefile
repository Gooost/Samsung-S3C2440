A  = a b c
B  = $(foreach f, $(A), $(f).o)

C  = a b c d/

D  = $(filter %/, $(C))
E  = $(filter-out %/, $(C))

files = $(wildcard *.c)


files1 = a.c b.c c.c d.c e.c a b c 
files2 = $(wildcard $(files1))


dep_files = $(patsubst  %.c, %.d, $(files1))

all:
	@echo B = $(B)
	@echo D = $(D)	
	@echo E = $(E)
	@echo files = $(files)
	@echo files2 = $(files2)	
	@echo dep_files = $(dep_files)	
	
