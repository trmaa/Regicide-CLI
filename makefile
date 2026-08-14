out_dir = REGICIDE
out = $(out_dir)/regicide

src_c = $(wildcard *.c)
src_s = $(wildcard *.s)
obj = $(addprefix obj/, $(src_c:.c=.o) $(src_s:.s=.o))

ccflags = -Wno-implicit-int -Wno-implicit-function-declaration
ldflags = -no-pie -lm

all: $(out)

$(out): $(obj) | $(out_dir)
	cc $^ -o $@ $(ldflags)

obj/%.o: %.c | obj
	cc -c $< -o $@ $(ccflags)

obj/%.o: %.s | obj
	cc -c $< -o $@ $(ccflags)

$(out_dir):
	mkdir -p $(out_dir)

obj:
	mkdir -p obj

clean:
	rm -r obj
	rm $(out)

run: $(out) | $(out_dir)
	cd $(out_dir); ./regicide
