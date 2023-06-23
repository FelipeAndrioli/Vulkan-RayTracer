#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <array>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>

#ifndef NDEBUG
const bool c_EnableValidationLayers = true;
#else
const bool c_EnableValidationLayers = false;
#endif

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> c_ValidationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

namespace Engine {

	const std::vector<const char*> c_DeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME	
	};

	struct ApplicationSpec {
		std::string Name = "Application.exe";
		uint32_t Width = 1600;
		uint32_t Height = 900;
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t>graphicsFamily;
		std::optional<uint32_t>presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct Vertex {
		// temporary, will move it to a better place later
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);
			
			return attributeDescriptions;
		}
	};

	class Application {
	public:
		Application(const ApplicationSpec &applicationSpec = ApplicationSpec());
		~Application();

		void Run();
		void Close();

	private:
		void Init();
		void InitGlfw();
		void InitVulkan();
		void Shutdown();

		void createVulkanInstance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createVertexBuffer();
		void createCommandBuffers();
		void createSyncObjects();
		void recreateSwapChain();
		void cleanupSwapChain();

		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void drawFrame();

	private:
		bool m_Running;
		GLFWwindow* m_Window;
		//VkInstance m_VulkanInstance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		//VkSurfaceKHR m_Surface;
		//VkPhysicalDevice m_PhysicalDevice;
		//VkDevice m_VulkanDevice;
		//VkQueue m_GraphicsQueue;
		//VkQueue m_PresentQueue;
		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
		VkRenderPass m_RenderPass;
		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_GraphicsPipeline;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;
		VkCommandPool m_CommandPool;
		std::vector<VkCommandBuffer> m_CommandBuffers;
		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;
		ApplicationSpec m_Spec;
		uint32_t m_CurrentFrame = 0;
		VkBuffer m_VertexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
	};
}
