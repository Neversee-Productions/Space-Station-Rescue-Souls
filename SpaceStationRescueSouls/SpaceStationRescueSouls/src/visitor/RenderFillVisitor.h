#ifndef _APP_VISITOR_RENDER_FILL_H
#define _APP_VISITOR_RENDER_FILL_H

namespace app::vis
{
	/// 
	/// @brief Used when needing to access our render fill variant.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// When utilizing the standard libraries variant to maintain type safety a visitor class is needed,
	/// this being one, is utilised to access the variant and assign appropriatly to app::vis::RenderFillVisitor::m_rectangleShape.
	/// </summary>
	class RenderFillVisitor
	{
	public: // Constructors/Destructor/Assignments
		RenderFillVisitor(sf::RectangleShape & rectangleShape);
		RenderFillVisitor(RenderFillVisitor const &) = default;
		RenderFillVisitor(RenderFillVisitor &&) = default;

		~RenderFillVisitor() = default;

		RenderFillVisitor & operator=(RenderFillVisitor const &) = default;
		RenderFillVisitor & operator=(RenderFillVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(std::shared_ptr<sf::Texture> & sptrTexture);
		void operator()(sf::Color & color);
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

		/// 
		/// @brief Reference to the rectangle shape we want to set.
		/// 
		/// <summary>
		/// Set the texture or fill colour of based on the operator() member function that is called.
		/// </summary>
		sf::RectangleShape & m_rectangleShape;
	};
}

#endif // !_APP_VISITOR_RENDER_FILL_H
