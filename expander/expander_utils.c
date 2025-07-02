#include "../library/parser.h"
#include "../library/minishell.h"


char *expand_string(const char *input, t_enviroment *env, int last_exit)//Tüm gelecek koşulları kontrol eden fonksiyonum result a stdup yer açıyourm "" şeklimde
// *p ile gelen lexer->word u tutucam ve onun üstüğnde gezip ona göre expand fonskionlara atıcam bana burda neden adresi ile yolladın dersen p üzerinden ilerlerjen
//*p işaret ettiği yeri kaybetmemek için ** yolladım ve (*p)++ ile ilerledim.
{
	char *result;
	const char *p;

	result = ft_strdup("");
	p = input;
	while (*p)
	{
		if (*p == '\'')
			expand_single_quote(&p, &result);
		else if (*p == '"')
			expand_double_quote(&p, &result, env, last_exit);
		else if (*p == '$')	
			expand_variable(&p, &result, env, last_exit);
		else
			append_normal_char(&p, &result);
	}
	return (result);
}



void expand_single_quote(const char **p, char **result) // '' tek tırnak için işlem yapar ft_strjoin_free önce strndupi le duplicate alır
//ve result a onu ekler en sonunda resultun başlangıç değerini freeledikten sonra. çıkar 
{
	const char *start;
	(*p)++;
	start = *p;
	while (**p && **p != '\'')
		(*p)++;
	*result = ft_strjoin_free(*result, ft_strndup(start, *p - start));
	if (**p)
		(*p)++;
}




void expand_double_quote(const char **p, char **result, t_enviroment *env, int last_exit) // "" Çift tırnak bakar ama çift tırnak için $
// olduğu için hem ona hemde normal char eklemeye bakar.
{
	(*p)++;
	while (**p && **p != '"')
	{
		if (**p == '$')
			expand_variable(p, result, env, last_exit);
		else
			append_normal_char(p, result);
	}
	if (**p)
		(*p)++;
}




void expand_variable(const char **p, char **result, t_enviroment *env, int last_exit) //$VAR veya $? expand eder. Variable genişletmek için kullanılır
//ve get_env?value değeri çekilip result a atılır. 
{
	const char *start;
	char *key;
	char *value;
	(*p)++;
	if (**p == '?')
	{
		*result = ft_strjoin_free(*result, ft_itoa(last_exit));
		(*p)++;
	}
	else
	{
		start = *p;
		while (**p && ft_isalnum(**p) || **p == '=')
			(*p)++;
		key = ft_strndup(start, (*p - start));
		value = get_env_value(key, env);
		*result = ft_strjoin_free(*result, value ? value : ft_strdup(""));
		free(key);
	}
}
//Note tek sorun 'HOME'1 -> HOME1 olması lazım ama bizde boşluk atıyor HOME 1

void append_normal_char(const char **p, char **result) //düz karakter normak olanları yapar.
{
	 *result = ft_strjoin_char(*result, **p);
    (*p)++;
}


