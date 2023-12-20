#include "gestor_usuarios.h"
#include "gestor_actividad.h"
#include <string>
#include "gtest/gtest.h"
using namespace std;

TEST(GestorUsuario, AltaUsuario)
{
	GestorUsuario gestor("usuarios.txt");
	srand(time(NULL));
	string nombreRandom = "usuario" + to_string(rand()%10000);
	EXPECT_FALSE(gestor.existeUsuario(nombreRandom));
	Usuario u;
	u.setUsuario(nombreRandom);
	u.setNombre("Nombre de prueba");
	u.setPass("1111prueba");
	EXPECT_TRUE(gestor.altaUsuario(u));
	EXPECT_FALSE(gestor.altaUsuario(u));
	EXPECT_TRUE(gestor.existeUsuario(nombreRandom));
}
// Prueba para la función mostrarActividadesEntreFechas
// TEST(GestorActividad, MostrarActividadesEntreFechas)
// {
//     // Configura tu objeto y las actividades según sea necesario
//     GestorActividad gestor("actividades.txt");
// 	srand(time(NULL));
// 	string fecha="fecha" + to_string(rand()%1)
// }
