#ifndef _COMPONENT_SHIELD_H
#define _COMPONENT_SHIELD_H

namespace app::comp
{
	/// 
	/// @brief Represents a entity that a player can pickup granting him a shield.
	/// @author Sebastian Kruzel
	/// 
	/// <summary>
	/// </summary>
	struct Shield
	{
	public: // Constructors/Destructor/Assignments
		Shield() = default;
		Shield(Shield const &) = default;
		Shield(Shield &&) = default;

		~Shield() = default;

		Shield & operator=(Shield const &) = default;
		Shield & operator=(Shield &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables

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

#endif // !_COMPONENT_SHIELD_H
