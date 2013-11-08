#include <GL/glew.h>

#include <algorithm>
#include <random>

#include <glow/Error.h>
#include <glow/Array.h>
#include <glow/logging.h>
#include <glow/Texture.h>
#include <glowutils/ScreenAlignedQuad.h>
#include <glowwindow/ContextFormat.h>
#include <glowwindow/Context.h>
#include <glowwindow/Window.h>
#include <glowwindow/WindowEventHandler.h>

using namespace glow;

class EventHandler : public WindowEventHandler
{
public:
    EventHandler()
    {
    }

    virtual ~EventHandler()
    {
    }

    void createAndSetupTexture();
	void createAndSetupGeometry();

    virtual void initialize(Window & window)
    {
        DebugMessageOutput::enable();

        glClearColor(0.2f, 0.3f, 0.4f, 1.f);

        createAndSetupTexture();
	    createAndSetupGeometry();
    }
    
    virtual void resizeEvent(
        Window & window
    ,   const unsigned int width
    ,   const unsigned int height)
    {
    	int side = std::min<int>(width, height);
        glViewport((width - side) / 2, (height - side) / 2, side, side);
    }

    virtual void paintEvent(Window & window)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_quad->draw();
    }

    virtual void idleEvent(Window & window)
    {
        window.repaint();
    }

protected:
    glow::ref_ptr<glow::Texture> m_texture;
    glow::ref_ptr<glow::ScreenAlignedQuad> m_quad;
};


/** This example shows ... .
*/
int main(int argc, char** argv)
{
    glewExperimental = GL_TRUE;

    ContextFormat format;

    Window window;
    window.assign(new EventHandler());

    window.create(format, "Simple Texture Example");
    window.show();

    return Window::run();
}

void EventHandler::createAndSetupTexture()
{
    static const int w(256);
    static const int h(256);
	unsigned char data[w * h * 4];

    std::random_device rd;
    std::mt19937 generator(rd());

    std::poisson_distribution<> r(0.2);

    for (int i = 0; i < w * h * 4; ++i)
        data[i] = 255 - static_cast<unsigned char>(r(generator) * 255);

	m_texture = new glow::Texture(GL_TEXTURE_2D);

	m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	m_texture->image2D(0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void EventHandler::createAndSetupGeometry()
{
    m_quad = new glow::ScreenAlignedQuad(m_texture);
    m_quad->setSamplerUniform(0);
}
