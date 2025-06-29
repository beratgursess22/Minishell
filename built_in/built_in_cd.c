#include "../library/minishell.h"
#include "../library/enviroment.h"

int built_in_cd(t_parser *parser, t_enviroment **env)
{
	char *target_directory; //gitmek istediğin hedef dizin
	char *old_pwd;
	char cwd[4096]; //current working directory
	old_pwd = get_env_value("PWD", *env); //pwd oldpwdde tutulacak, pwd değişecek.
	if (parser->args[2]) //cd 1 argüman almalı.
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	if(!parser->args[1])//cd'ye argüman verilmezse dizin home'a döner.
	{
		target_directory = get_env_value("HOME", *env);
		if (!target_directory)//home yoksa hata
		{
			ft_putendl_fd("hata home kısmı", 2);
			return (1);
		}
	}
	else
		target_directory = parser->args[1];
	//chdir düzgün çalıştığında 0 döndürür.
	if (chdir(target_directory) != 0)//chdir çalıştığı için başarılı olduğunda dizin değişmiş olacak.
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target_directory); //sistemden gelen hata mesajını direkt eklemek için
		return (1);
	}
	
	if (old_pwd)//eski PWD -> OLDPWD olmalı.
		update_env_value("OLDPWD", old_pwd, env);
	if (getcwd(cwd, sizeof(cwd))) //PWD yi yeni pwd ile değiştir.
		update_env_value("PWD", cwd, env);
	return (0);
}

// chdir(target) -> dizini target'la değiştirir.
// getcwd(buf, size) -> o anki çalışma dizininin tam pathini verir.
// | Parametre | Açıklama                                                               |
// | --------- | ---------------------------------------------------------------------- |
// | `buf`     | Çalışma dizinini yazmak için kullanılacak karakter dizisi (char array) |
// | `size`    | `buf` dizisinin boyutu (`sizeof(cwd)` gibi)                            |
