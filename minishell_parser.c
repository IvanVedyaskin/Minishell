#include "minishell.h"


int		count_list(t_command *command)
{
	int	count;

	count = 0;
	while (command != NULL)
	{
		++count;
		command = command->next;
	}
	return (count);
}
char	**parser(t_command **command)
{
	char		**str;
	t_command	*tmp;
	int 	i;

	tmp = *command;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (count_list(tmp) + 1));
	if (!str)
		return (NULL);
	while (i < count_list(*command))
	{
		str[i] = (char *)malloc(sizeof(char) * ft_strlen(tmp->str));
		if (!str[i])
			return (NULL);
		ft_strcopy(str[i], tmp->str);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

// пока лист
// 	если &this == &next
//		значит, что дошел до следующей части.
// пока лист
//	Если this == $
//		если &this == &next
//			Значит это отправится на проверку переменной окружения
//	Если this == '
//		внутри данных ковычек все "" остаются и внутри не расерываются. Нужно доходить до самой дальней '. Отсальные 					одинарные ковычки опускаются
//