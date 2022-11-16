#include "utils.h"

/**
 * is_env_change - checks if a variable in environment
 * @incr: 1 or 0, increment or not
 * Return: int
 * Description: cant use globals var cause betty, so i'm wrapping it.
 */
int is_env_change(int incr)
{
	static int env_c; /* initialized to 0 by def, betty complained */

	if (incr)
		env_c++;
	return (env_c);
}

/**
 * _is_in_env - checks if a variable in environment
 * @name: name of variable
 * Return: ptr of env variable or NULL
 */
char *_is_in_env(char *name)
{
	int i, j;

	if (!name)
		return (NULL);
	/* iterate ovver env variables */
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		/* iterate over name */
		while (name[j])
		{
			/* immediately break if no match */
			if (name[j] != environ[i][j])
				break;
			/* if next is null, and next in env variable is '=' */
			if (name[j + 1] == '\0' && environ[i][j + 1] == '=')
				return (environ[i]);
			j++;
		}
	}

	return (NULL);
}

/**
 * _getenv - gets a variable from environment
 * @name: name of variable
 * Return: string of env variable or NULL
 */
char *_getenv(char *name)
{
	int i = 0;
	char *var;

	if (!name)
		return (NULL);
	/* check in env */
	var = _is_in_env(name);
	if (!var)
		return (NULL);
	/* its in env and we have var pointer */
	while (var[i])
	{
		/* look for the = */
		if (var[i] == '=')
			return (&var[i + 1]);
		i++;
	}

	return (NULL);
}

/**
 * _setenv - sets a variable to environment
 * @name: name of variable
 * @value: value of variable
 * @overwrite: 0 if no ovewrite, 1 to overwrite
 * Return: string of env variable or NULL
 */
int _setenv(char *name, char *value, int overwrite)
{
	char *exist = NULL, *var = NULL, **env = environ, **new_env = NULL;
	int env_s = 0, i;

	if (!name || !value)
		return (-1);
	exist = _is_in_env(name);
	if (exist && !overwrite)
		return (INV);
	/* get environment size */
	env_s = lst_size(env);
	if (!exist) /* if it doesnt exist, add one for new */
		env_s++;
	/* make array buffer */
	new_env = malloc(sizeof(char *) * (env_s + 1));
	if (!new_env)
		return (BNF);
	new_env[env_s] = NULL; /* add null byte to end */
	/* new value */
	var = _strconcatv(name, 2, "=", value);
	if (!var)
	{
		free(new_env);
		return (BNF);
	}
	/* copy env while adding new var */
	for (i = 0; i < env_s; i++)
	{
		if (exist && (env[i] == exist)) /* env exist, ovewrite with newvar */
			new_env[i] = var;
		else if (!exist && i == (env_s - 1))
			new_env[i] = var; /* env does not exist, add new var */
		else if (env[i])
			new_env[i] = _strdup(env[i]); /* dupijng to free easily later */
	}
	/* replace old env */
	environ = new_env;
	if (is_env_change(0)) /* if was called before, free previous pointer */
		free_lst(env), free(env);
	is_env_change(1);
	return (OK);
}

/**
 * _unsetenv - sets a variable to environment
 * @name: name of variable
 * Return: string of env variable or NULL
 */
int _unsetenv(char *name)
{
	char *exist = NULL, **env = environ, **new_env = NULL;
	int env_s = 0, i = 0, j = 0;

	if (!name)
		return (ANV);
	exist = _is_in_env(name);
	if (!exist)
		return (ANV);
	/* it esixts, get environment size */
	env_s = lst_size(env);
	/* make array buffer */
	new_env = malloc(sizeof(char *) * env_s);
	if (!new_env)
		return (BNF);
	new_env[env_s - 1] = '\0'; /* add null byte to end */
	while (env[i])
	{
		if (exist && (env[i] == exist))
		{
			i++;
			continue; /* skip the exist */
		}
		new_env[j] = _strdup(env[i]), i++, j++;
	}

	/* replace old env */
	environ = new_env;
	if (is_env_change(0)) /* if was called before, free previous pointer */
		free_lst(env), free(env);
	is_env_change(1);
	return (OK);
}
