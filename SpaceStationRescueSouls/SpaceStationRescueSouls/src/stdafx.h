// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#ifdef _DEBUG

/*********************************/
/**    BEGIN Debug Libraries    **/
/*********************************/

#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#pragma comment(lib,"thor-d.lib")

/*********************************/
/**     END Debug Libraries     **/
/*********************************/

#else

/*********************************/
/**   BEGIN Release Libraries   **/
/*********************************/

#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#pragma comment(lib,"thor.lib")

/*********************************/
/**    END Release Libraries    **/
/*********************************/

#endif

/*********************************/
/** BEGIN Independant Libraries **/
/*********************************/
/*********************************/
/**  END Independant Libraries  **/
/*********************************/

// STL Common C libraries
#include <cstddef>
#include <cstdint>

// STL Containers
#include <iterator>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <queue>

// STL Dynamic Memory Management Libraries
#include <new>
#include <scoped_allocator>
#include <memory>
#include <memory_resource>

// STL Error Libraries
#include <exception>
#include <stdexcept>
#include <system_error>

// STL Utility libraries
#include <type_traits>
#include <random>
#include <chrono>
#include <functional>
#include <tuple>
#include <initializer_list>
#include <limits>
#include <variant>
#include <optional>

// STL Input/Output libraries
#include <string>
#include <sstream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <filesystem>

// STL Multithreading libraries
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>

// SFML Library
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

// Thor Library
#include <Thor/Animations.hpp>
#include <Thor/Config.hpp>
#include <Thor/Graphics.hpp>
#include <Thor/Input.hpp>
#include <Thor/Math.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Resources.hpp>

// Entt Library
#include <Entt/entt.hpp>

//
// Includes here
//

#include "input/Keyhandler.h"
#include "input/MouseHandler.h"

#include "math/Math.h"
#include "math/Vector2.h"

#include "utilities/Time.h"
#include "utilities/Console.h"

#include "Registry.h"

namespace app::inp
{
	using KeyHandler = Keyhandler<sf::Keyboard::Key>;
	using MouseHandler = Mousehandler<sf::Mouse::Button>;
}

