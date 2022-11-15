#include "Render.hpp"
#include "Ray.hpp"

void Render::render(Scene& scene)
{
	std::vector<Vector3f> framebuffer(scene.width * scene.height);
	double scale = std::tan(deg2rad(scene.fov / 2));
	double imageAspectRatio = scene.width / (float)scene.height;
	Vector3f eyePose(278, 273, -800);
	int m = 0;
	int spp = 16;
	for (int j = 0; j < scene.height; ++j)
	{
		for (int i = 0; i < scene.width; ++i)
		{
			
			double x = (2 * (i + 0.5) / (scene.width) - 1) * imageAspectRatio * scale;
			double y = (1 - 2 * (j + 0.5) / (scene.height)) * scale;

			Vector3f dir = Vector3f(-x, y, 1).normalized();//���������˴��������ϵ�任����������ϵ�Ĺ��̡����������ϵ�������ǣ�x,y,-1��
			for (int a = 0; a < spp; ++a)
			{
				framebuffer[m] += scene.CastRay(Ray(eyePose, dir), 0) / spp;
			}
			++m;
		}
		UpdateProgress(j / (float)scene.height);
	}
	UpdateProgress(1.f);

	// save framebuffer to file
	FILE* fp = fopen("binary.ppm", "wb");
	(void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
	for (auto i = 0; i < scene.height * scene.width; ++i) {
		static unsigned char color[3];
		color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].x), 0.6f));
		color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].y), 0.6f));
		color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].z), 0.6f));
		fwrite(color, 1, 3, fp);
	}
	fclose(fp);
}