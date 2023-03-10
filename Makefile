NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I./includes #-fsanitize=address
EXTRA_FLAGS = -O3 -Imlx_linux -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

RM = rm -f

#$(VERBOSE).SILENT:

HEADER = header.h

INC = -I ./includes

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.c										\
			map_file_checker/check_file_type.c			\
			map_file_checker/check_map_walls.c			\
			map_file_checker/check_textures.c			\
			map_file_checker/check_file.c				\
			map_file_checker/check_map.c				\
			map_file_checker/check_map_elements.c		\
			map_file_checker/checker_utils.c			\
			map_file_checker/get_doors_info.c			\
			map_file_checker/get_map_textures.c			\
			map_file_checker/get_map_textures_rgb.c		\
			map_file_checker/get_map_content.c			\
			map_file_checker/get_next_line.c			\
			map_file_checker/get_map_utils.c			\
			map_file_checker/map_resizer.c				\
			map_file_checker/get_player_info.c			\
			map_file_checker/map.c						\
			minimap/minimap.c							\
			minimap/minimap_draw_player.c				\
			minimap/minimap_utils.c						\
			player/player.c								\
			player/player_rot_mouse.c					\
			mouse/mouse.c								\
			mouse/mouse_hook.c							\
			raycast/raycast.c							\
			raycast/raycast_update.c					\
			raycast/raycast_door.c						\
			raycast/raycast_wall.c						\
			raycast/raycast_utils.c						\
			raycast/raycast_utils2.c					\
			draw_utils/draw_utils.c						\
			draw_utils/draw_utils2.c					\
			draw_utils/draw_utils_2d.c					\
			init_data_pointers.c						\
			free_map_memory.c							\
			free_memory_utils.c							\
			alloc_memory.c								\
			error_handler.c								\
			math_utils.c								\
			utils.c										\
			render_scene_2d.c							\
			render_scene_3d.c							\
			ray.c										\
			time.c										\
			key_controls.c								\
			collisions.c								\
			doors.c										\
			setup_textures.c							\
			frame_count.c

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	cd mlx_linux && make && cd ..
	$(CC) $(CFLAGS) $(OBJS) $(INC) $(EXTRA_FLAGS) -o $(NAME)
	@echo "\033[1;36m[cub3D COMPILED]\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p objects
	mkdir -p objects/map_file_checker
	mkdir -p objects/minimap
	mkdir -p objects/player
	mkdir -p objects/mouse
	mkdir -p objects/raycast
	mkdir -p objects/draw_utils
	$(CC) -c $(CFLAGS) -I/usr/include -Imlx_linux -O3 $(INC) $< -o $@

norminette:
	clear
	@./norm.sh

clean:
	cd mlx_linux && make clean && cd ..
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re force norminette
