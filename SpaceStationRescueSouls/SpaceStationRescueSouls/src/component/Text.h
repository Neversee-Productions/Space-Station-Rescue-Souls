#ifndef _COMPONENT_TEXT_H
#define _COMPONENT_TEXT_H

namespace app::comp
{
	/// 
	/// @brief Represents a rectangle that displays text.
	/// @author Sebastian Kruzel
	/// 
	/// <summary>
	/// </summary>
	struct Text
	{
	public: // Constructors/Destructor/Assignments
		Text() = default;
		~Text() = default;

		Text(Text const &) = default;
		Text(Text &&) = default;

		Text & operator=(Text const &) = default;
		Text & operator=(Text &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::string textToDisplay;
		sf::Text text;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_COMPONENT_TEXT_H
