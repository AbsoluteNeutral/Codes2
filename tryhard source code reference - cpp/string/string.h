#ifndef _STRING_H
#define _STRING_H

#include <iostream>

namespace zg 
{
	//__________________________________________________ Function
	size_t strlen	(const char* string_);
	void strcpy		(char* dest_, const char* source_);
	void strncpy	(char* dest_, const char* source_, size_t num_);

	//__________________________________________________ Class
	class string
	{
	public:
		
		string	() noexcept;
		string	(const char* string_) noexcept;	
		string	(const string& rhs_) noexcept;	//copy ctor
		string	(string&& rhs_) noexcept;				//move ctor
		~string	();

		string& operator=		(const string& rhs_);	//copy operator
		string& operator=		(string&& rhs_);			//move operator
		string& operator+=	(const char* rhs_);
		string& operator+=	(const string& rhs_);
		friend std::ostream& operator<<(std::ostream& os, const string& string_);
		
		const char& at		(size_t position_) const throw();
		
		char&				back	();
		const char& back	() const;
		
		void 				clear	();
		const char* cstr	() const;
		const char* c_str	() const;
		
		char& 			front	();
		const char& front	() const;
		
		void 				pushback(const char* string_);
		void 				pushback(const string& string_);

		size_t			length() const;
		size_t			size() const;
		
	private:
		char* buffer;
		char* end;
	};

} // namespace zg

#endif
