#include <iostream>

/*I will create in the future a separate function responsible for validating one software-version component.

For every character, convert it to unsigned char and check:
1. Is it between ASCII 0x21 and 0x7E?
2. Is it different from '-'?
If either condition fails, reject the input.

Why unsigned char?

Because passing a negative char to functions such as std::isprint() can cause undefined behavior. Also, std::isprint() is locale-sensitive, whereas the SSH specification requires US-ASCII.
You can implement this validation yourself without relying on locale-dependent character functions.

*/

std::string* SSH_ID_GEN(std::string name , std::string version)
{
	if (name.find("-") != std::string::npos || name.empty() || version.empty())
	{
		return nullptr;
	}

	std::string ssh_id = "SSH-2.0-" + name + "_" + version + "\r\n";

	if (ssh_id.size() > 255)
	{
		return nullptr;
	}	       

	std::string* ssh_id_ptr = new std::string(ssh_id);

	return ssh_id_ptr; // user has to free after use
}
