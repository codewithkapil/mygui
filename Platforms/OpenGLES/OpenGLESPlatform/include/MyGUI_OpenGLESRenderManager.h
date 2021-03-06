#ifndef MYGUI_OPENGLES_RENDER_MANAGER_H__
#define MYGUI_OPENGLES_RENDER_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_RenderFormat.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_RenderManager.h"
#include "MyGUI_OpenGLESImageLoader.h"

namespace MyGUI
{

	class OpenGLESRenderManager :
		public RenderManager,
		public IRenderTarget
	{
	public:
		OpenGLESRenderManager();

		void initialise(OpenGLESImageLoader* _loader = nullptr);
		void shutdown();

		static OpenGLESRenderManager& getInstance();
		static OpenGLESRenderManager* getInstancePtr();

		/** @see RenderManager::getViewSize */
		virtual const IntSize& getViewSize() const;

		/** @see RenderManager::getVertexFormat */
		virtual VertexColourType getVertexFormat();

		/** @see RenderManager::isFormatSupported */
		virtual bool isFormatSupported(PixelFormat _format, TextureUsage _usage);

		/** @see RenderManager::createVertexBuffer */
		virtual IVertexBuffer* createVertexBuffer();
		/** @see RenderManager::destroyVertexBuffer */
		virtual void destroyVertexBuffer(IVertexBuffer* _buffer);

		/** @see RenderManager::createTexture */
		virtual ITexture* createTexture(const std::string& _name);
		/** @see RenderManager::destroyTexture */
		virtual void destroyTexture(ITexture* _texture);
		/** @see RenderManager::getTexture */
		virtual ITexture* getTexture(const std::string& _name);

		/** @see IRenderTarget::begin */
		virtual void begin();
		/** @see IRenderTarget::end */
		virtual void end();
		/** @see IRenderTarget::doRender */
		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);
		/** @see IRenderTarget::getInfo */
		virtual const RenderTargetInfo& getInfo();

		/** @see RenderManager::setViewSize */
		void setViewSize(int _width, int _height) override;

		/** @see RenderManager::registerShader */
		void registerShader(
			const std::string& _shaderName,
			const std::string& _vertexProgramFile,
			const std::string& _fragmentProgramFile) override;

		/* for use with RTT, flips Y coordinate when rendering */
		void doRenderRtt(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

		/*internal:*/
		void drawOneFrame();
		bool isPixelBufferObjectSupported() const;
		unsigned int getShaderProgramId(const std::string& _shaderName);

	private:
		std::string loadFileContent(const std::string& _file);
		unsigned int createShaderProgram(const std::string& _vertexProgramFile, const std::string& _fragmentProgramFile);
		void destroyAllResources();

	private:
		IntSize mViewSize;
		bool mUpdate;
		VertexColourType mVertexFormat;
		RenderTargetInfo mInfo;
		unsigned int mDefaultProgramId;
		std::map<std::string, unsigned int> mRegisteredShaders;
		unsigned int mReferenceCount; // for nested rendering
		int mYScaleUniformLocation;

		typedef std::map<std::string, ITexture*> MapTexture;
		MapTexture mTextures;
		OpenGLESImageLoader* mImageLoader;
		bool mPboIsSupported;

		bool mIsInitialise;
	};

} // namespace MyGUI

#endif // MYGUI_OPENGLES_RENDER_MANAGER_H__
