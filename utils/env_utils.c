#include "utils.h"


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
    return (1);
  /* get environment size */
  env_s = lst_size(env);
  if (!exist) /* if it doesnt exist, add one for new */
    env_s++;
  /* make array buffer */
  new_env = malloc(sizeof(char *) * (env_s + 1));
  if (!new_env)
    return (-1);
  var = _strconcatv(name, 2, "=", value);
  if (!var)
  {
    free (new_env);
    return (-1);
  }
  /* copy env while adding new var */
  for (i = 0; i < env_s; i++)
  {
    if (exist && (environ[i] == exist)) /* env var exist, ovewrite with new var */
      new_env[i] = var;
    else if (!exist && i == (env_s - 1))
      new_env[i] = var; /* env does not exist, add new var */
    else
      new_env[i] = env[i];
  }
  new_env[env_s] = '\0'; /* add null byte to end */
  /* replace old env */
  environ = new_env;
	return (0);
}

/**
 * _unsetenv - sets a variable to environment
 * @name: name of variable
 * @value: value of variable
 * Return: string of env variable or NULL
 */
int _unsetenv(char *name)
{
  char *exist = NULL, **env = environ, **new_env = NULL;
  int env_s = 0, i = 0, j = 0;

  if (!name)
    return (-1);
  exist = _is_in_env(name);
  if (!exist)
    return (0);
  /* it esixts, get environment size */
  env_s = lst_size(env);
  /* make array buffer */
  new_env = malloc(sizeof(char *) * env_s);
  if (!new_env)
    return (-1);
  new_env[env_s - 1] = '\0'; /* add null byte to end */
  while (env[i])
  {
    if (exist && (env[i] == exist))
    {
      i++;
      continue; /* skip the exist */
    }
    new_env[j] = env[i], i++, j++;
  }

  /* replace old env */
  environ = new_env;
  return (0);
}
