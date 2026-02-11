NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -pedantic

INCLUDES_BASE	= -I./base/includes -I./Libft -I./mlx_linux

INCLUDES_BONUS	= -I./bonus/includes -I./Libft -I./mlx_linux

SRC_DIR		= base/srcs
ENG_DIR		= base/engine

SRC_DIR_BONUS = bonus/srcs
ENG_DIR_BONUS = bonus/engine

MAKEFLAGS += -s

LIBFT_DIR	= Libft
MLX_DIR		= mlx_linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -O2 -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS_PARS		= base/main.c \
			  $(SRC_DIR)/validate_input.c \
			  $(SRC_DIR)/init_structs.c \
			  $(SRC_DIR)/read_file.c \
			  $(SRC_DIR)/identify_elements.c \
			  $(SRC_DIR)/parse_file.c \
			  $(SRC_DIR)/parse_texture.c \
			  $(SRC_DIR)/parse_color.c \
			  $(SRC_DIR)/extract_map.c \
			  $(SRC_DIR)/validate_map_borders.c \
			  $(SRC_DIR)/validate_map_chars.c \
			  $(SRC_DIR)/validate_map.c \
			  $(SRC_DIR)/cleanup.c \
			  $(SRC_DIR)/utils/parse_utils.c \
			  $(SRC_DIR)/utils/parse_texture_utils.c \
			  $(SRC_DIR)/utils/parse_color_utils.c \
			  $(SRC_DIR)/utils/extract_map_utils.c \
			  $(SRC_DIR)/utils/map_validation_utils.c \
			  $(SRC_DIR)/utils/validate_map_chars_utils.c \
			  $(SRC_DIR)/utils/validate_map_borders_utils.c \
			  $(SRC_DIR)/utils/init_structs_utils.c \
			  $(SRC_DIR)/utils/cleanup_utils.c

SRCS_ENG		=  $(ENG_DIR)/init.c \
			  $(ENG_DIR)/utils.c \
			  $(ENG_DIR)/key_management.c \
			  $(ENG_DIR)/key_utils.c \
			  $(ENG_DIR)/move_management.c \
			  $(ENG_DIR)/rotation.c \
			  $(ENG_DIR)/ray_casting.c \
			  $(ENG_DIR)/ray_casting_utils.c \
			  $(ENG_DIR)/dda_implementation.c \
			  $(ENG_DIR)/colours_management.c \
			  $(ENG_DIR)/draw.c \
			  $(ENG_DIR)/texture.c \
			  $(ENG_DIR)/main_rendering.c \
			  $(ENG_DIR)/fps.c

SRCS_PARS_BONUS	= bonus/main.c \
			  $(SRC_DIR_BONUS)/validate_input.c \
			  $(SRC_DIR_BONUS)/init_structs.c \
			  $(SRC_DIR_BONUS)/read_file.c \
			  $(SRC_DIR_BONUS)/identify_elements.c \
			  $(SRC_DIR_BONUS)/parse_file.c \
			  $(SRC_DIR_BONUS)/parse_texture.c \
			  $(SRC_DIR_BONUS)/parse_color.c \
			  $(SRC_DIR_BONUS)/extract_map.c \
			  $(SRC_DIR_BONUS)/validate_map_borders.c \
			  $(SRC_DIR_BONUS)/validate_map_chars.c \
			  $(SRC_DIR_BONUS)/validate_map.c \
			  $(SRC_DIR_BONUS)/cleanup.c \
			  $(SRC_DIR_BONUS)/utils/parse_utils.c \
			  $(SRC_DIR_BONUS)/utils/parse_texture_utils.c \
			  $(SRC_DIR_BONUS)/utils/parse_color_utils.c \
			  $(SRC_DIR_BONUS)/utils/extract_map_utils.c \
			  $(SRC_DIR_BONUS)/utils/map_validation_utils.c \
			  $(SRC_DIR_BONUS)/utils/validate_map_chars_utils.c \
			  $(SRC_DIR_BONUS)/utils/validate_map_borders_utils.c \
			  $(SRC_DIR_BONUS)/utils/init_structs_utils.c \
			  $(SRC_DIR_BONUS)/utils/cleanup_utils.c

SRCS_ENG_BONUS	= $(ENG_DIR_BONUS)/init.c \
			  $(ENG_DIR_BONUS)/arms.c \
			  $(ENG_DIR_BONUS)/arms_utils.c \
			  $(ENG_DIR_BONUS)/utils.c \
			  $(ENG_DIR_BONUS)/doors.c \
			  $(ENG_DIR_BONUS)/door_init.c \
			  $(ENG_DIR_BONUS)/key_management.c \
			  $(ENG_DIR_BONUS)/key_utils.c \
			  $(ENG_DIR_BONUS)/mouse_management.c \
			  $(ENG_DIR_BONUS)/move_management.c \
			  $(ENG_DIR_BONUS)/rotation.c \
			  $(ENG_DIR_BONUS)/ray_casting.c \
			  $(ENG_DIR_BONUS)/ray_casting_utils.c \
			  $(ENG_DIR_BONUS)/dda_implementation.c \
			  $(ENG_DIR_BONUS)/colours_management.c \
			  $(ENG_DIR_BONUS)/draw.c \
			  $(ENG_DIR_BONUS)/texture_select.c \
			  $(ENG_DIR_BONUS)/texture_draw.c \
			  $(ENG_DIR_BONUS)/texture.c \
			  $(ENG_DIR_BONUS)/main_rendering.c \
			  $(ENG_DIR_BONUS)/fps.c \
			  $(ENG_DIR_BONUS)/minimap.c \
			  $(ENG_DIR_BONUS)/minimap_utils.c

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
GRAY		= \033[0;90m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(SRCS_PARS) $(SRCS_ENG)
	@echo "$(GRAY)Linking $(NAME) (BASE)...$(RESET)"
	@$(CC) $(INCLUDES_BASE) $(CFLAGS) $(SRCS_PARS) $(SRCS_ENG) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

bonus: $(LIBFT) $(MLX) $(SRCS_PARS_BONUS) $(SRCS_ENG_BONUS)
	@echo "$(GRAY)Linking $(NAME_BONUS) (BONUS)...$(RESET)"
	@$(CC) $(INCLUDES_BONUS) $(CFLAGS) $(SRCS_PARS_BONUS) $(SRCS_ENG_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(GRAY)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@echo "$(GRAY)Compiling MLX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

clean:
	@echo "$(GRAY)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@rm -f *.o

fclean: clean
	@echo "$(GRAY)Cleaning executable and libraries...$(RESET)"
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)All cleaned!$(RESET)"

re: fclean all

re_bonus: fclean bonus

test: $(NAME)
	@echo "$(YELLOW)Running test with maps/test.cub...$(RESET)"
	@./$(NAME) maps/test.cub

test_bonus: bonus
	@echo "$(YELLOW)Running test bonus with maps/test.cub...$(RESET)"
	@./$(NAME_BONUS) maps/test.cub

debug: CFLAGS += -g -fsanitize=address -DDEBUG
debug: 
	@echo "$(GRAY)Building in debug mode with AddressSanitizer...$(RESET)"
	@$(MAKE) re --no-print-directory
	@echo "$(GRAY)(Debug mode enabled)$(RESET)"

debug_bonus: CFLAGS += -g -fsanitize=address -DDEBUG
debug_bonus:
	@echo "$(GRAY)Building bonus in debug mode with AddressSanitizer...$(RESET)"
	@$(MAKE) re_bonus --no-print-directory
	@echo "$(GRAY)(Debug mode enabled)$(RESET)"

.PHONY: all bonus clean fclean re re_bonus test test_bonus debug debug_bonus
.SILENT:
