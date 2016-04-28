/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>

namespace ejson {
	/**
	 * @brief Position in the file of the original data.
	 */
	class FilePos {
		private:
			size_t m_col; //!< source text colomn
			size_t m_line; //!< source Line colomn
		public:
			/**
			 * @brief default contructor (set line and col at 0)
			 */
			FilePos();
			/**
			 * @brief initialize constructor
			 * @param[in] _line Line in the file
			 * @param[in] _col Colomn in the file
			 */
			FilePos(size_t _line, size_t _col);
			/**
			 * @brief Increment the colomn position
			 * @return Reference on this
			 */
			FilePos& operator ++();
			/**
			 * @brief Decrement the colomn position
			 * @return Reference on this
			 */
			FilePos& operator --();
			/**
			 * @brief Addition operator
			 * @param[in] _obj Addition object..
			 * @return Reference on this
			 */
			FilePos& operator +=(const FilePos& _obj);
			/**
			 * @brief Colomn addition operator
			 * @param[in] _col Number of colomn to add
			 * @return Reference on this
			 */
			FilePos& operator +=(size_t _col);
			/**
			 * @brief Asignment operator
			 * @param[in] _obj Object to copy
			 * @return Reference on this
			 */
			FilePos& operator= (const FilePos& _obj);
			/**
			 * @brief Find a new line & reset colomn at 0
			 */
			void newLine();
			/**
			 * @brief Check if the value is a new line and update internal property
			 * @param[in] _val Char value to check
			 * @return true We find a new line
			 * @return false We NOT find a new line
			 */
			bool check(char32_t _val);
			/**
			 * @brief Setter of specific data
			 * @param[in] _line Line in the file
			 * @param[in] _col Colomn in the file
			 */
			void set(size_t _line, size_t _col);
			/**
			 * @brief Reset position at 0,0
			 */
			void clear();
			/**
			 * @brief Get the colomn position
			 * @return Colomn in number of utf8-char
			 */
			size_t getCol() const;
			/**
			 * @brief Get the line number position
			 * @return line ID (start at 0)
			 */
			size_t getLine() const;
	};
	//! @not-in-doc
	std::ostream& operator <<(std::ostream& _os, const FilePos& _obj);
	
}

