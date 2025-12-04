#  ========================  #
#							 #
#  	   -*-  CUB3D -*-		 #
#							 #
#  ========================  #

#  ========================  #
#			COLORS			 #
#  ========================  #
RED		=	\033[1;31m
PURPLE	=	\033[1;35m
GREEN	=	\033[1;32m
RESET	=	\033[0m

#  ========================  #
#	    FILE STRUCTURE		 #
#  ========================  #
NAME		=	cub3D

LIB			=	lib
MLX_DIR		=	MLX42
LIBFT_DR	=	libft
SRCS_DR		=	srcs
OBJS_DR		=	objs
INC_DR		=	incs

LIBFT_INC	=	$(LIB)/$(LIBFT_DR)/$(INC_DR)
MLX_INC		=	$(MLX_DIR)/include/$(MLX_DIR)

#  ========================  #
#	      COMMANDS			 #
#  ========================  #
MAKE	=	make -s -C
RM		=	rm -rf

#  ========================  #
#		FILES AND PATHS		 #
#  ========================  #
LIBFT	=	$(LIB)/$(LIBFT_DR)/libft.a

SRCS	=	$(shell find $(SRCS_DR) -name '*.c')		# Remove wild cards at campus
OBJS	=	$(patsubst $(SRCS_DR)/%.c,$(OBJS_DR)/%.o,$(SRCS))

#  ========================  #
#	   COMPILATION RULES	 #
#  ========================  #
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror \
			-I$(LIBFT_INC) \
			-I$(INC_DR) \
			-I$(MLX_INC)

MLX_LBS	=	-L$(MLX_DIR) -lmlx42 -ldl -lglfw -lm -pthread

#  ========================  #
#			RULES			 #
#  ========================  #
all		:	$(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

# Compile .o files into objs/
$(OBJS_DR)/%.o	:	$(SRCS_DR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


#  ========================  #
#		  BUILDING			 #
#  ========================  #
$(NAME)		:	$(LIBFT) $(OBJS)
	@if [ "$(MAKECMDGOALS)" != "re" ]; then \
		echo "$(PURPLE)🔗 Creating cub3d executable...\n$(RESET)"; \
	fi
	@$(CC) $(CFLAGS) $(OBJS) \
	$(LIBFT) $(MLX_LBS) \
	-o $(NAME)


$(LIBFT)	:
	@if [ "$(MAKECMDGOALS)" != "re" ]; then \
		echo "$(GREEN)\n📦 Creating Libft...$(RESET)"; \
	else \
		echo "$(GREEN)\n🔄 Rebuilding everything...$(RESET)\n"; \
	fi
	@$(MAKE) $(LIB)/$(LIBFT_DR)

#  ========================  #
#		  CLEANING			 #
#  ========================  #
clean	:
	@if [ "$(MAKECMDGOALS)" != "fclean" ] && [ "$(MAKECMDGOALS)" != "re" ]; then \
		echo "$(RED)\n🧹 Cleaning object files...\n$(RESET)"; \
	fi
	@$(RM) $(OBJS_DR)
	@$(MAKE) $(LIB)/$(LIBFT_DR) clean

fclean	:	clean
	@if [ "$(MAKECMDGOALS)" != "re" ]; then \
		echo "$(RED)\n💥 Cleaning everything...\n$(RESET)"; \
	fi
	@$(RM) $(NAME)
	@$(MAKE) $(LIB)/$(LIBFT_DR) fclean

#  ========================  #
#							 #
#  	     -*- END -*-		 #
#							 #
#  ========================	 #