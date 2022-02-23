#include "../../includes/minishell.h"

static void add_pwd(char *name, char *value)
{
	t_param	*param;

	param = (t_param *) malloc(sizeof (t_param));
	if (param == NULL)
		return ;
	param->name = ft_strdup(name);
	if (param->name == NULL)
	{
		free(param);
		return ;
	}
	param->value = value;
	add_param(&g_common->env, param);
}

static void	update_pwd(char *name, char *value)
{
	int 	flag;
	t_param	*param;

	flag = check_presence_param(&param, name);
	if (flag == ENV_PARAM)
	{
		free(param->value);
		param->value = value;
	}
	else
	{
		if (flag == LOCAL_PARAM)
			delete_param(&g_common->local_param, param);
		add_pwd(name, value);
	}
}

static void	update_all_pwd(void)
{
	update_pwd(OLD_PWD, g_common->pwd);
	g_common->pwd = getcwd(NULL, 0);
	update_pwd(PWD, ft_strdup(g_common->pwd));
}

static void dir_tire(void)
{
	int		flag;
	t_param	*param;

	flag = check_presence_param(&param, OLD_PWD);
	if (flag == NEW_PARAM)
	{
		printf("%s: %s: %s not set\n", NAME, C_CD, OLD_PWD);
		return ;
	}
	else if (flag == LOCAL_PARAM)
		write(1, "\n", 1);
	else if (flag == ENV_PARAM)
	{
		if (chdir(param->value) == -1)
		{
			printf("%s: %s: %s: %s\n", NAME, C_CD, param->value, strerror(errno));
			return ;
		}
		else
		{
			update_all_pwd();
			pwd();
		}
	}
}

void	cd(char *dir)
{
	if (dir != NULL && ft_strcmp(dir, TIRE) == 0)
		dir_tire();
	else
	{
		if (dir == NULL || ft_strcmp(dir, TILDA) == 0)
			dir = g_common->home;
		if (chdir(dir) == -1)
			printf("%s: %s: %s: %s\n", NAME, C_CD, dir, strerror(errno));
		else
			update_all_pwd();
	}
}
