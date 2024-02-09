/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:58:07 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:23 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// FREE
char		*free_ptr(char *ptr);

// LEXER
static char	*filler(char *input, int pos);
char		**lexer(char *input);

// UTILS
int			check_quotes(char c, int quotes);

#endif