#include "TemperamentDeterminant.h"

const TemperamentDeterminant::Genre genres[24] = {
		// Genre											speed	positivity
		{ TemperamentDeterminant::GenreTypes::Fiction,		0.9f,	0.7f },
		{ TemperamentDeterminant::GenreTypes::Fantasy,		0.4f,	0.6f },
		{ TemperamentDeterminant::GenreTypes::Horror,		0.5f,	0.1f },
		{ TemperamentDeterminant::GenreTypes::Thriller,		0.5f,	0.3f },
		{ TemperamentDeterminant::GenreTypes::Mystic,		0.4f,	0.2f },
		{ TemperamentDeterminant::GenreTypes::ActionFilm,	1.0f,	0.6f },
		{ TemperamentDeterminant::GenreTypes::Drama,		0.5f,	0.3f },
		{ TemperamentDeterminant::GenreTypes::Detective,	0.3f,	0.4f },
		{ TemperamentDeterminant::GenreTypes::Adventures,	0.7f,	0.9f },
		{ TemperamentDeterminant::GenreTypes::Comedy,		0.6f,	1.0f },
		{ TemperamentDeterminant::GenreTypes::Documentary,	0.1f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Melodrama,	0.3f,	0.4f },
		{ TemperamentDeterminant::GenreTypes::Family,		0.3f,	0.8f },
		{ TemperamentDeterminant::GenreTypes::Cartoon,		0.6f,	1.0f },
		{ TemperamentDeterminant::GenreTypes::Historical,	0.5f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Military,		0.6f,	0.2f },
		{ TemperamentDeterminant::GenreTypes::Crime,		0.8f,	0.3f },
		{ TemperamentDeterminant::GenreTypes::Western,		0.7f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Biography,	0.1f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Sport,		0.6f,	0.6f },
		{ TemperamentDeterminant::GenreTypes::TVWebShow,	0.3f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Anime,		0.5f,	0.5f },
		{ TemperamentDeterminant::GenreTypes::Music,		0.1f,	0.7f },
		{ TemperamentDeterminant::GenreTypes::Musical,		0.1f,	0.8f },
	};

TemperamentDeterminant::TemperamentDeterminant()
{
	clear();
}

void TemperamentDeterminant::saveMoviesParametersToScv(const char* path)
{
	std::ofstream f;
	f.open(path);
	f << "\"\",\"Speed\"\"Positivity\",\"Mark\"\n";
	for (int i = 0; i < movies.size(); i++)
		f << "\"" << i + 1 << "\"," << movies[i].speed << "," << movies[i].positivity << "," << movies[i].mark << "\n";
	f.close();
}

void TemperamentDeterminant::addMovieParameters(std::vector<GenreTypes> genresVector, float mark)
{
	Movie movie;

	float speed = 0.0f;
	float positivity = 0.0f;

	// averaging genre parameters
	for (int i = 0; i < genresVector.size(); i++)
	{
		speed += genres[genresVector[i]].speed;
		positivity += genres[genresVector[i]].positivity;
	}

	movie.speed = speed / genresVector.size();
	movie.positivity = positivity / genresVector.size();
	movie.mark = mark;
	movies.push_back(movie);
}

void TemperamentDeterminant::clear()
{
	movies.clear();
}