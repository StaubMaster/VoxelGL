
#ifndef KEYCHECK_HPP
# define KEYCHECK_HPP
# include "../openGL.h"

class KeyCheck
{
	protected:
		int	key;
		int(*check_func)(GLFWwindow *, int);

	public:
		KeyCheck(int key, bool isMouse);

		virtual bool	check() const = 0;
		virtual void	update(GLFWwindow * win) = 0;
};

class KeyHold : public KeyCheck
{
	private:
		bool hold;

	public:
		KeyHold(int key, bool isMouse);

		bool	check() const;
		void	update(GLFWwindow * win);
};

class KeyPress : public KeyCheck
{
	private:
		bool press;
		bool hold;

	public:
		KeyPress(int key, bool isMouse);

		bool	check() const;
		void	update(GLFWwindow * win);
};

#endif
