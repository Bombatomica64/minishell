/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:32 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/15 12:28:13 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"

//built-in functions
/**
 * @brief echo builtin function
 * @param matrix with echo + arguments
 * @return TRUE if success, FALSE if error
 * @note it will only accept -n as a flag
*/
int		ft_echo(char **mtx);

/**
 * @brief cd builtin function
 * @param str matrix with cd + arguments
 * @param data struct with envp
 * @return TRUE if success, FALSE if error
*/
int		ft_cd(char **str, t_data *data);

/**
 * @brief env builtin function
 * @param envp matrix with env + arguments
 * @note the environment variables are stored in data->envp
*/
void	ft_env(char **envp);

/**
 * @brief pwd builtin function
 * @note print the current working directory
*/
void	ft_pwd(void);

/**
 * @brief export builtin function
 * @param envp pointer to the environment variables
 * @param cmd matrix with export + arguments
 * @return TRUE if success, FALSE if error
*/
int		ft_export(char ***envp, char **cmd);

t_bool	add_or_update(char ***envp, char *tmp, char **cmd, int j);

/**
 * @brief unset builtin function
 * @param mtx matrix with unset + arguments
 * @param envp pointer to the environment variables
 * @return TRUE if success, FALSE if error
 */
int		ft_unset(char **mtx, char ***envp);

// unset helper functions
/**
 * @brief remove an entry from the environment variables
 * @param envp pointer to the environment variables
 * @param entry entry to remove
*/
void	remove_envp_entry(char ***envp, char *entry);

// export  helper functions

/**
 * @brief add a new entry to the environment variables
 * @param envp pointer to the environment variables
 * @param str entry to add
 * @return TRUE if success, FALSE if error
*/
t_bool	add_to_env(char ***envp, char *str);

/**
 * @brief update an entry in the environment variables
 * @param envp pointer to the environment variables
 * @param str entry to update
 * @return TRUE if success, FALSE if error
*/
t_bool	update_env(char ***envp, char *str);

// debug functions

/**
 * @brief print the environment variables
 * @param envp matrix with the environment variables
 * @note used for debugging 
*/
void	print_pwds(char **envp);

/**
 * @brief Replaces the tilde ~ character in a string with the corresponding path
 * @param str The input string containing the tilde character
 * @param data data structure containing the information for path replacement
 * @return The modified string with ~ replaced by the corresponding path
 */
char	*ft_tilde(char *str, t_data *data);

// take a file and output absolute path
char	*refactor_path(char *str, t_data *data, int i);
char	*ft_remove_chars(char *str, char *to_remove, int i);

t_bool	is_exit(char *command);
int		ft_exit(char **cmd, t_data *data);

#endif