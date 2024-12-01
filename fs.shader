//fs.shader
//fs.shader
#version 460

in vec3 position_eye, normal_eye;
uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

// C�c bi?n uniform ?? b?t/t?t t?ng ngu?n s�ng
uniform bool enable_light_1; // B?t/t?t ngu?n s�ng 1
uniform bool enable_light_2; // B?t/t?t ngu?n s�ng 2

void main() {
    vec3 final_color = vec3(0);

    //-----------Ngu?n s�ng 1-------------
    if (enable_light_1) {
        vec3 light_position_world_1 = vec3(0.0, 2.27, -3.0);
        vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        vec3 Ld_1 = vec3(0.7, 0.7, 0.7);
        vec3 Kd_1 = vec3(1.0, 1.0, 1.0);
        vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

        vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 20.0);
        vec3 Ls_1 = vec3(0.2, 0.2, 0.2);
        vec3 Ks_1 = vec3(1.0, 1.0, 1.0);
        vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

        vec3 La_1 = vec3(0.2, 0.2, 0.2);
        vec3 Ka_1 = vec3(1.0, 1.0, 1.0);
        vec3 Ia_1 = La_1 * Ka_1;

        final_color += (Is_1 + Id_1 + Ia_1);
    }
    else{
        vec3 light_position_world_1 = vec3(0.0, 2.27, 1.0);
        vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        vec3 Ld_1 = vec3(0,0,0);
        vec3 Kd_1 = vec3(0,0,0);
        vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

        vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 20.0);
        vec3 Ls_1 = vec3(0,0,0);
        vec3 Ks_1 = vec3(0,0,0);
        vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

        vec3 La_1 = vec3(0,0,0);
        vec3 Ka_1 = vec3(0,0,0);
        vec3 Ia_1 = La_1 * Ka_1;

        
        final_color += (Is_1 + Id_1 + Ia_1);}

    //-----------Ngu?n s�ng 2-------------
    if (enable_light_2) {
        vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);
        vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
        vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
        vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

        float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
        vec3 Ld_2 = vec3(0.7, 0.7, 0.7);
        vec3 Kd_2 = vec3(1, 0.5, 0);
        vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

        vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
        float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
        float specular_factor_2 = pow(dot_prod_specular_2, 50.0);
        vec3 Ls_2 = vec3(0.8, 0.8, 1.0);
        vec3 Ks_2 = vec3(0.7, 0.7, 0.7);
        vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

        vec3 La_2 = vec3(0.1, 0.1, 0.3);
        vec3 Ka_2 = vec3(0.5, 0.5, 0.5);
        vec3 Ia_2 = La_2 * Ka_2;

        
        final_color += (Is_2 + Id_2 + Ia_2);
    }else{
        vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);
        vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
        vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
        vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

        float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
        vec3 Ld_2 = vec3(0,0,0);
        vec3 Kd_2 = vec3(0,0,0);
        vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

        vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
        float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
        float specular_factor_2 = pow(dot_prod_specular_2, 50.0);
        vec3 Ls_2 = vec3(0,0,0);
        vec3 Ks_2 = vec3(0,0,0);
        vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

        vec3 La_2 = vec3(0,0,0);
        vec3 Ka_2 = vec3(0,0,0);
        vec3 Ia_2 = La_2 * Ka_2;

        final_color += (Is_2 + Id_2 + Ia_2);}

    // ------------M�u cu?i c�ng t? c�c ngu?n s�ng------------
    out_color = vec4(final_color, 1.0) * fragment_color;
}

/*#version 460

in vec3 position_eye, normal_eye;
uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

void main() {
    //-----------ch? ??nh c�c v? tr� ngu?n s�ng-------------
    // Ngu?n s�ng 1
    vec3 light_position_world_1 = vec3(0.0, 2.27, -3);//trong ph�ng
    vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));

    // Ngu?n s�ng 2
    vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);//m?t tr?i
    vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));

    // V? tr� viewer
    vec3 position_viewer = vec3(0.0, 0.0, 0.0);

    // Chu?n h�a normal_eye
    vec3 n_eye = normalize(normal_eye);

    // --------------�nh s�ng t? ngu?n 1---------------------
    vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
    vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
    vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

    float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
    vec3 Ld_1 = vec3(0.7, 0.7, 0.7); // �nh s�ng khu?ch t�n t? ngu?n 1
    vec3 Kd_1 = vec3(1.0, 0.5, 0.0); // H? s? ph?n x? khu?ch t�n t? ngu?n 1
    vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

    vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
    float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
    float specular_factor_1 = pow(dot_prod_specular_1, 100.0); // H? s? s�ng b�ng t? ngu?n 1
    vec3 Ls_1 = vec3(0.2, 0.2, 0.2);
    vec3 Ks_1 = vec3(1.0, 1.0, 1.0);
    vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

    vec3 La_1 = vec3(0.2, 0.2, 0.2);
    vec3 Ka_1 = vec3(1.0, 1.0, 1.0);
    vec3 Ia_1 = La_1 * Ka_1;

    // --------------�nh s�ng t? ngu?n 2---------------------
    vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
    vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
    vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

    float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
    vec3 Ld_2 = vec3(1.5,1.5,1.5);//vec3 Ld_2 = vec3(0.6, 0.6, 0.8); // �nh s�ng khu?ch t�n t? ngu?n 2
    vec3 Kd_2 = vec3(0.5, 1.0, 0.5); // H? s? ph?n x? khu?ch t�n t? ngu?n 2
    vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

    vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
    float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
    float specular_factor_2 = pow(dot_prod_specular_2, 50.0); // H? s? s�ng b�ng t? ngu?n 2
    vec3 Ls_2 = vec3(0.8, 0.8, 1.0);
    vec3 Ks_2 = vec3(0.7, 0.7, 0.7);
    vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

    vec3 La_2 = vec3(0.1, 0.1, 0.3);
    vec3 Ka_2 = vec3(0.5, 0.5, 0.5);
    vec3 Ia_2 = La_2 * Ka_2;

    // ------------M�u cu?i c�ng t? hai ngu?n s�ng------------
    vec3 final_color = (Is_1 + Id_1 + Ia_1) + (Is_2 + Id_2 + Ia_2);
    out_color = vec4(final_color, 1.0) * fragment_color;
}*/


/*#version 460

in vec3 
	position_eye,
	normal_eye;

uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color; 

void main() {
	
	//-----------ch? ??nh c�c v? tr�-------------
		// v? tr� ngu?n s�ng trong th? gi?i
	vec3 light_position_world = vec3(0.0, 2.27, 0.0);
	//vec3 light_position_world = vec3(0.0, 1.0, 0.0);
		// bi?n ??i v? tr� ngu?n s�ng sang eye space
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

		// v? tr� viewer
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);
		
		// chu?n h�a normal_eye
	vec3 n_eye = normalize(normal_eye);

		// t�nh vector kho?ng c�ch t? ngu?n s�ng ??n m?t
		// h??ng vector h??ng t? vertex ??n ngu?n s�ng
		// = v? tr� Light - v? tr� Vertex
	vec3 distance_to_light_eye = light_position_eye - position_eye;
		// chu?n h�a vector kho?ng c�ch t? ngu?n s�ng ??n m?t
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

		// t�nh vector kho?ng c�ch v? tr� viewer v� vertex
		// = v? tr� viewer - v? tr� vertex
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
		// chu?n h�a	
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);

	// --------------c??ng ?? �nh s�ng khu?ch t�n-----------------------
		// t�nh cosin g�c gi?a vector h??ng �nh s�ng v� vector ph�p tuy?n: l.n
	float dot_prod = dot(direction_to_light_eye, n_eye);
		// l?y gi� tr? >=0 ?? lo?i b? gi� tr? �m ?ng v?i g�c >90 ??
	dot_prod = max(dot_prod, 0.0);

		// c??ng ?? �nh s�ng ??n
		// m�u tr?ng m?
	vec3 Ld = vec3(0.7, 0.7, 0.7);
	//vec3 Ld = vec3(1.5, 1.5, 1.5);

		// h? s? ph?n x? khu?ch t�n
		// m�u cam
	vec3 Kd = vec3(1.0, 1.0, 1.0);

		// c??ng ?? �nh s�ng khu?ch t�n cu?i c�ng
	vec3 Id = Ld * Kd * dot_prod;

	// -----------------c??ng ?? �nh s�ng ph?n x?-------------------
	//vec3 surface_to_viewer_eye = normalize(0.0 - position_eye);

		// t�nh ph?n x?
		// ??o d?u direction_to_light_eye
		// v� ??i s? th? 1 c?a h�m reflect l� vector h??ng t? ngu?n s�ng ??n vertex
		// m� direction_to_light_eye hi?n ?ang c� h??ng t? vertex ??n ngu?n s�ng
	vec3 reflection_eye = reflect(-direction_to_light_eye, n_eye);

		// t�nh cosin g�c gi?a: v.r
	float dot_prod_specular = dot(surface_to_viewer_eye, reflection_eye);
		// l?y gi� tr? >=0 ?? lo?i b? gi� tr? �m ?ng v?i g�c >90 ??
	dot_prod_specular = max(dot_prod_specular, 0.0);

		// h? s? s�ng b�ng
	float specular_exponent = 100.0;
		// t�nh m? v?i h? s? s�ng b�ng
	float specular_factor = pow(dot_prod_specular, specular_exponent);

		// �nh s�ng ph?n x?
		// m�u tr?ng
	vec3 Ls = vec3(1.0, 1.0, 1.0);

		// h? s? ph?n x?
		// ph?n x? to�n ph?n, m�u tr?ng
	vec3 Ks = vec3(1.0, 1.0, 1.0);

		// c??ng ?? �nh s�ng ph?n x? cu?i c�ng
	vec3 Is = Ls * Ks * specular_factor;

	// --------------c??ng ?? �nh s�ng m�i tr??ng---------------
		// �nh s�ng m�i tr??ng
		// m�u x�m
	vec3 La = vec3(0.2, 0.2, 0.2);

		// h? s? m�i tr??ng
		// ph?n chi?u ho�n to�n
	vec3 Ka = vec3(1.0, 1.0, 1.0);

		// c??ng ?? �nh s�ng m�i tr??ng cu?i c�ng
	vec3 Ia = La * Ka;

	// ---------m�u cu?i c�ng------------
	//out_color = fragment_color;
	//out_color = vec4(Is + Id + Ia, 1.0);
	out_color = vec4(Is + Id + Ia, 1.0)* fragment_color;
}*/
