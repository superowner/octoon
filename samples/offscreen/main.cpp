#include <octoon/octoon.h>

#include <octoon/game_object.h>
#include <octoon/game_application.h>
#include <octoon/camera_component.h>
#include <octoon/path_meshing_component.h>
#include <octoon/mesh_renderer_component.h>
#include <octoon/transform_component.h>
#include <octoon/first_person_camera.h>
#include <octoon/video_feature.h>
#include <octoon/video/text_material.h>

const std::string chars[] =
{
	R"({"paths":[{"points":[[602.54,436.40,8],[602.54,436.40,3],[602.54,443.41,3],[602.54,443.41,3],[602.54,451.51,3],[600.25,458.11,3],[595.66,463.22,3],[591.07,468.33,3],[585.33,470.88,3],[578.45,470.88,3],[573.38,470.88,3],[569.43,469.51,3],[566.60,466.76,3],[563.76,464.01,3],[562.34,460.51,3],[562.34,456.27,3],[562.34,450.81,3],[563.87,446.89,3],[566.92,444.48,3],[569.97,442.08,3],[575.27,440.34,3],[582.80,439.26,3],[582.80,439.26,3],[602.54,436.40,3],[602.54,436.40,3],[602.54,436.40,9]],"w":0.00,"h":0.00},{"points":[[608.97,475.04,8],[608.97,475.04,3],[608.97,428.35,3],[608.97,428.35,3],[608.97,419.60,3],[606.96,412.93,3],[602.93,408.34,3],[598.90,403.76,3],[593.19,401.46,3],[585.79,401.46,3],[581.76,401.46,3],[577.46,402.21,3],[572.90,403.70,3],[568.33,405.19,3],[564.72,407.00,3],[562.08,409.12,3],[562.08,409.12,3],[562.08,416.92,3],[562.08,416.92,3],[569.57,410.55,3],[577.26,407.37,3],[585.14,407.37,3],[596.74,407.37,3],[602.54,415.08,3],[602.54,430.49,3],[602.54,430.49,3],[580.46,433.80,3],[580.46,433.80,3],[563.84,436.40,3],[555.52,443.97,3],[555.52,456.53,3],[555.52,462.38,3],[557.52,467.21,3],[561.50,471.04,3],[565.48,474.88,3],[570.89,476.79,3],[577.73,476.79,3],[583.06,476.79,3],[587.91,475.33,3],[592.28,472.41,3],[596.65,469.49,3],[599.99,465.58,3],[602.28,460.69,3],[602.28,460.69,3],[602.54,460.69,3],[602.54,460.69,3],[602.54,460.69,3],[602.54,475.04,3],[602.54,475.04,3],[602.54,475.04,3],[608.97,475.04,3],[608.97,475.04,3],[608.97,475.04,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[572.93,415.78,8],[577.52,410.17,3],[583.99,407.37,3],[592.35,407.37,3],[599.36,407.37,3],[604.98,410.01,3],[609.20,415.29,3],[613.42,420.57,3],[615.53,427.70,3],[615.53,436.66,3],[615.53,446.92,3],[613.23,455.19,3],[608.65,461.47,3],[604.06,467.74,3],[598.10,470.88,3],[590.79,470.88,3],[583.38,470.88,3],[577.41,468.31,3],[572.86,463.15,3],[568.32,458.00,3],[566.04,451.81,3],[566.04,444.58,3],[566.04,444.58,3],[566.04,435.55,3],[566.04,435.55,3],[566.04,427.98,3],[568.34,421.39,3],[572.93,415.78,3],[572.93,415.78,9]],"w":0.00,"h":0.00},{"points":[[590.20,476.79,8],[599.68,476.79,3],[607.40,473.09,3],[613.35,465.69,3],[619.31,458.28,3],[622.28,448.56,3],[622.28,436.53,3],[622.28,425.75,3],[619.72,417.21,3],[614.59,410.91,3],[609.46,404.61,3],[602.32,401.46,3],[593.19,401.46,3],[587.47,401.46,3],[582.21,402.90,3],[577.41,405.78,3],[572.60,408.66,3],[568.92,412.74,3],[566.37,418.02,3],[566.37,418.02,3],[566.04,418.02,3],[566.04,418.02,3],[566.04,418.02,3],[566.04,368.73,3],[566.04,368.73,3],[566.04,368.73,3],[559.62,368.73,3],[559.62,368.73,3],[559.62,368.73,3],[559.62,475.04,3],[559.62,475.04,3],[559.62,475.04,3],[566.04,475.04,3],[566.04,475.04,3],[566.04,475.04,3],[566.04,462.24,3],[566.04,462.24,3],[566.04,462.24,3],[566.37,462.24,3],[566.37,462.24,3],[571.52,471.94,3],[579.47,476.79,3],[590.20,476.79,3],[590.20,476.79,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[606.11,465.17,8],[600.79,468.98,3],[594.53,470.88,3],[587.34,470.88,3],[579.46,470.88,3],[573.13,468.06,3],[568.35,462.41,3],[563.57,456.76,3],[561.17,449.28,3],[561.17,439.97,3],[561.17,430.36,3],[563.79,422.52,3],[569.03,416.46,3],[574.27,410.40,3],[581.09,407.37,3],[589.49,407.37,3],[595.64,407.37,3],[601.26,408.95,3],[606.37,412.11,3],[606.37,412.11,3],[606.37,404.84,3],[606.37,404.84,3],[601.26,402.59,3],[595.96,401.46,3],[590.46,401.46,3],[579.90,401.46,3],[571.25,405.10,3],[564.52,412.37,3],[557.79,419.64,3],[554.42,428.97,3],[554.42,440.36,3],[554.42,451.23,3],[557.42,460.02,3],[563.41,466.73,3],[569.41,473.44,3],[577.28,476.79,3],[587.02,476.79,3],[594.42,476.79,3],[600.79,475.14,3],[606.11,471.86,3],[606.11,471.86,3],[606.11,465.17,3],[606.11,465.17,3],[606.11,465.17,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[610.59,444.71,8],[610.59,452.03,3],[608.35,458.22,3],[603.87,463.28,3],[599.39,468.35,3],[593.06,470.88,3],[584.88,470.88,3],[577.91,470.88,3],[572.21,468.19,3],[567.80,462.80,3],[563.38,457.41,3],[561.17,449.75,3],[561.17,439.84,3],[561.17,429.75,3],[563.63,421.82,3],[568.54,416.04,3],[573.46,410.26,3],[579.68,407.37,3],[587.22,407.37,3],[594.36,407.37,3],[600.04,409.70,3],[604.26,414.35,3],[608.48,419.01,3],[610.59,424.67,3],[610.59,431.33,3],[610.59,431.33,3],[610.59,444.71,3],[610.59,444.71,3],[610.59,444.71,9]],"w":0.00,"h":0.00},{"points":[[617.09,475.04,8],[617.09,475.04,3],[617.09,368.73,3],[617.09,368.73,3],[617.09,368.73,3],[610.59,368.73,3],[610.59,368.73,3],[610.59,368.73,3],[610.59,414.71,3],[610.59,414.71,3],[610.59,414.71,3],[610.33,414.71,3],[610.33,414.71,3],[605.74,405.88,3],[598.08,401.46,3],[587.34,401.46,3],[577.60,401.46,3],[569.68,405.05,3],[563.58,412.24,3],[557.47,419.43,3],[554.42,428.80,3],[554.42,440.36,3],[554.42,451.75,3],[557.21,460.66,3],[562.80,467.12,3],[568.38,473.57,3],[575.59,476.79,3],[584.42,476.79,3],[590.18,476.79,3],[595.35,475.46,3],[599.94,472.80,3],[604.53,470.13,3],[608.00,466.53,3],[610.33,461.99,3],[610.33,461.99,3],[610.59,461.99,3],[610.59,461.99,3],[610.59,461.99,3],[610.59,475.04,3],[610.59,475.04,3],[610.59,475.04,3],[617.09,475.04,3],[617.09,475.04,3],[617.09,475.04,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[561.43,433.54,8],[562.47,425.10,3],[565.20,418.63,3],[569.62,414.12,3],[574.03,409.62,3],[579.62,407.37,3],[586.37,407.37,3],[592.87,407.37,3],[597.95,409.65,3],[601.63,414.22,3],[605.31,418.79,3],[607.30,425.23,3],[607.61,433.54,3],[607.61,433.54,3],[561.43,433.54,3],[561.43,433.54,3],[561.43,433.54,9]],"w":0.00,"h":0.00},{"points":[[614.36,439.38,8],[614.36,439.38,3],[614.36,436.53,3],[614.36,436.53,3],[614.36,425.70,3],[611.97,417.15,3],[607.18,410.88,3],[602.40,404.60,3],[595.55,401.46,3],[586.63,401.46,3],[577.10,401.46,3],[569.36,405.05,3],[563.38,412.24,3],[557.41,419.43,3],[554.42,428.26,3],[554.42,438.74,3],[554.42,450.81,3],[557.28,460.18,3],[562.99,466.82,3],[568.71,473.47,3],[576.20,476.79,3],[585.46,476.79,3],[594.60,476.79,3],[602.89,474.15,3],[610.33,468.87,3],[610.33,468.87,3],[610.33,461.99,3],[610.33,461.99,3],[602.67,467.92,3],[594.81,470.88,3],[586.76,470.88,3],[578.79,470.88,3],[572.54,468.10,3],[567.99,462.54,3],[563.45,456.98,3],[561.17,449.26,3],[561.17,439.38,3],[561.17,439.38,3],[614.36,439.38,3],[614.36,439.38,3],[614.36,439.38,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[591.05,368.92,8],[589.05,368.01,3],[586.52,367.56,3],[583.45,367.56,3],[577.78,367.56,3],[573.03,369.53,3],[569.23,373.47,3],[565.42,377.41,3],[563.51,383.17,3],[563.51,390.74,3],[563.51,390.74,3],[563.51,403.21,3],[563.51,403.21,3],[563.51,403.21,3],[550.59,403.21,3],[550.59,403.21,3],[550.59,403.21,3],[550.59,409.12,3],[550.59,409.12,3],[550.59,409.12,3],[563.51,409.12,3],[563.51,409.12,3],[563.51,409.12,3],[563.51,475.04,3],[563.51,475.04,3],[563.51,475.04,3],[569.94,475.04,3],[569.94,475.04,3],[569.94,475.04,3],[569.94,409.12,3],[569.94,409.12,3],[569.94,409.12,3],[588.97,409.12,3],[588.97,409.12,3],[588.97,409.12,3],[588.97,403.21,3],[588.97,403.21,3],[588.97,403.21,3],[569.94,403.21,3],[569.94,403.21,3],[569.94,403.21,3],[569.94,391.26,3],[569.94,391.26,3],[569.94,379.40,3],[574.36,373.47,3],[583.19,373.47,3],[586.70,373.47,3],[589.31,374.14,3],[591.05,375.48,3],[591.05,375.48,3],[591.05,368.92,3],[591.05,368.92,3],[591.05,368.92,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})",
	R"({"paths":[{"points":[[610.59,445.03,8],[610.59,452.27,3],[608.31,458.38,3],[603.74,463.38,3],[599.17,468.38,3],[593.02,470.88,3],[585.27,470.88,3],[578.04,470.88,3],[572.21,468.17,3],[567.80,462.73,3],[563.38,457.30,3],[561.17,449.67,3],[561.17,439.84,3],[561.17,430.06,3],[563.58,422.20,3],[568.38,416.27,3],[573.19,410.34,3],[579.55,407.37,3],[587.47,407.37,3],[594.36,407.37,3],[599.93,409.69,3],[604.20,414.32,3],[608.46,418.95,3],[610.59,424.45,3],[610.59,430.81,3],[610.59,430.81,3],[610.59,445.03,3],[610.59,445.03,3],[610.59,445.03,9]],"w":0.00,"h":0.00},{"points":[[617.09,403.21,8],[617.09,403.21,3],[610.59,403.21,3],[610.59,403.21,3],[610.59,403.21,3],[610.59,414.58,3],[610.59,414.58,3],[610.59,414.58,3],[610.33,414.58,3],[610.33,414.58,3],[605.57,405.83,3],[597.91,401.46,3],[587.34,401.46,3],[577.47,401.46,3],[569.52,405.09,3],[563.48,412.34,3],[557.44,419.59,3],[554.42,428.93,3],[554.42,440.36,3],[554.42,451.83,3],[557.21,460.77,3],[562.80,467.18,3],[568.38,473.59,3],[575.59,476.79,3],[584.42,476.79,3],[596.02,476.79,3],[604.66,471.90,3],[610.33,462.11,3],[610.33,462.11,3],[610.59,462.11,3],[610.59,462.11,3],[610.59,462.11,3],[610.59,471.47,3],[610.59,471.47,3],[610.59,492.42,3],[600.68,502.90,3],[580.85,502.90,3],[574.10,502.90,3],[566.93,500.80,3],[559.35,496.60,3],[559.35,496.60,3],[559.35,503.29,3],[559.35,503.29,3],[566.67,506.92,3],[573.79,508.74,3],[580.72,508.74,3],[593.15,508.74,3],[602.31,505.61,3],[608.22,499.36,3],[614.13,493.10,3],[617.09,483.22,3],[617.09,469.71,3],[617.09,469.71,3],[617.09,403.21,3],[617.09,403.21,3],[617.09,403.21,9]],"w":0.00,"h":0.00}],"w":0.00,"h":0.00,"x":0.00,"y":0.00,"ft":0})"
};

class AutoRotation : public octoon::GameComponent
{
public:
	void onActivate() override
	{
		this->addComponentDispatch(octoon::GameDispatchType::Frame);
	}

	void onDeactivate() noexcept override
	{
		this->removeComponentDispatch(octoon::GameDispatchType::Frame);
	}

	void onFrame() override
	{
		this->getComponent<octoon::TransformComponent>()->setLocalQuaternionAccum(octoon::math::Quaternion().make_rotation_y(0.01f));
	}

	octoon::GameComponentPtr clone() const noexcept
	{
		return std::make_shared<AutoRotation>();
	}
};

int main(int argc, const char* argv[])
{
	int w = 1920, h = 1080;

	auto app = std::make_shared<octoon::GameApplication>();
	app->open(nullptr, w, h, w, h);
	app->start();

	auto material = std::make_shared<octoon::video::TextMaterial>();
	material->setLean(0.0f);
	material->setExtrude(5.0f);
	material->setTextColor(octoon::video::TextColor::FrontColor, octoon::math::float3(31.0, 179.0, 249.0) / 255.0f);
	material->setTextColor(octoon::video::TextColor::SideColor, octoon::math::float3(0.0, 1.0, 0.0));

	auto camera = std::make_shared<octoon::GameObject>();
	camera->addComponent<octoon::CameraComponent>();
	camera->getComponent<octoon::CameraComponent>()->setCameraOrder(octoon::video::CameraOrder::Main);
	camera->getComponent<octoon::CameraComponent>()->setClearColor(octoon::math::float4(1.0, 1.0, 1.0, 0.0));
	camera->getComponent<octoon::CameraComponent>()->setCameraType(octoon::video::CameraType::Ortho);
	camera->getComponent<octoon::CameraComponent>()->setOrtho(octoon::math::float4(0.0, 1.0, 0.0, 1.0));
	camera->addComponent<octoon::FirstPersonCameraComponent>();

	auto object = std::make_shared<octoon::GameObject>();
	object->addComponent<octoon::PathMeshingComponent>(chars[0]);
	object->addComponent<octoon::MeshRendererComponent>(material);
	object->addComponent<AutoRotation>();

	app->update();
	app->getFeature<octoon::VideoFeature>()->saveAsPNG("output.png", 0, 0, w, h);
}