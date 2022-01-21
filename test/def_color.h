/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:17:36 by sikeda            #+#    #+#             */
/*   Updated: 2021/10/10 15:17:37 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_COLOR_H
# define DEF_COLOR_H

/*
** Text color
*/
# define COLOR_NORMAL		""
# define COLOR_RESET		"\033[m"

# define COLOR_BLACK		"\033[30m"
# define COLOR_RED			"\033[31m"
# define COLOR_GREEN		"\033[32m"
# define COLOR_YELLOW		"\033[33m"
# define COLOR_BLUE			"\033[34m"
# define COLOR_MAGENTA		"\033[35m"
# define COLOR_CYAN			"\033[36m"
# define COLOR_WHITE		"\033[37m"

/*
** Text bold color
*/
# define COLOR_B			"\033[1m"

# define COLOR_B_BLACK		"\033[1;30m"
# define COLOR_B_RED		"\033[1;31m"
# define COLOR_B_GREEN		"\033[1;32m"
# define COLOR_B_YELLOW		"\033[1;33m"
# define COLOR_B_BLUE		"\033[1;34m"
# define COLOR_B_MAGENTA	"\033[1;35m"
# define COLOR_B_CYAN		"\033[1;36m"
# define COLOR_B_WHITE		"\033[1;37m"

/*
** Text background color
*/
# define COLOR_BG_RESET		"\033[49m"

# define COLOR_BG_BLACK		"\033[40m"
# define COLOR_BG_RED		"\033[41m"
# define COLOR_BG_GREEN		"\033[42m"
# define COLOR_BG_YELLOW	"\033[43m"
# define COLOR_BG_BLUE		"\033[44m"
# define COLOR_BG_MAGENTA	"\033[45m"
# define COLOR_BG_CYAN		"\033[46m"
# define COLOR_BG_WHITE		"\033[47m"

#endif
