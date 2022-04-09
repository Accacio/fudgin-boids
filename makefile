# Boids
#
all: boids
boids: src/boids.c
	@gcc $< -Os -lncursesw -lm -ltcc -lpthread -ldl -o $@


# end
