/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:02:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/24 00:55:19 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//TODO дать определенным ошибкам определенные коды
# define ERROR_NUM_MALLOC       -1
# define ERROR_NUM_READ         -1
# define ERROR_NUM_FILE_DIR     -1
# define ERROR_NUM_FILE         -1
# define ERROR_NUM_DIR          -1
# define ERROR_NUM_ENV          -1

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