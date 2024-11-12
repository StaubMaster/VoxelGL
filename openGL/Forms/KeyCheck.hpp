
#ifndef KEYCHECK_HPP
# define KEYCHECK_HPP
# include "../openGL.h"

class KeyCheck
{
	protected:
		int	key;

	public:
		KeyCheck(int key);

		virtual bool	check() const = 0;
		virtual void	update(GLFWwindow * win) = 0;
};

class KeyPress : public KeyCheck
{
	private:
		bool press;
		bool hold;

	public:
		KeyPress(int key);

		bool	check() const;
		void	update(GLFWwindow * win);
};

#endif
