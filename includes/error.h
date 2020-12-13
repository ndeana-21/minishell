/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:02:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/13 01:36:57 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EXIT_FAILURE           1
# define EXIT_SUCCESS           0

# define ERROR_SYNTAX           "minishell: invalid syntax"
# define ERROR_ENV              "minishell: have no env data"
# define ERROR_PARAMS_LEAST     "minishell: not enough params"
# define ERROR_PARAMS_MANY      "minishell: too many params"
# define ERROR_MALLOC           "minishell: invalid allocation"
# define ERROR_READ             "minishell: invalid reading"
# define ERROR_FILE_DIR         "minishell: no such file/directory"
# define ERROR_FILE             "minishell: no such file"
# define ERROR_DIR              "minishell: no such directory"
# define ERROR_OPTION           "minishell: no such option"
# define ERROR_COMMAND          "minishell: command not found"

#endif
