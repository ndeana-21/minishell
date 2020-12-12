/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:02:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/11 13:44:34 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EXIT_FAILURE           1
# define EXIT_SUCCESS           0

# define ERROR_SYNTAX           "ERROR invalid syntax"
# define ERROR_ENV              "ERROR have no env data"
# define ERROR_PARAMS_LEAST     "ERROR not enough params"
# define ERROR_PARAMS_MANY      "ERROR too many params"
# define ERROR_MALLOC           "ERROR allocation"
# define ERROR_READ             "ERROR reading"
# define ERROR_FILE_DIR         "ERROR no such file/directory"
# define ERROR_FILE             "ERROR no such file"
# define ERROR_DIR              "ERROR no such directory"
# define ERROR_OPTION           "ERROR no such option"
# define ERROR_COMMAND          "ERROR command not found"

#endif
