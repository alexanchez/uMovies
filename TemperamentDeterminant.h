#pragma once

#include <vector>
#include <fstream>

/*
Каждому фильму присвоено 2 числа путем усреднения чисел его жанров.
В csv файл, на обучение ии, посылаются такие данные:
	Х - speed, positivity (0-1) (этими числами можно определить коеффициенты всех 4 темпераментов)
	У - оценка фильма (0-1)
в файл идут все просмотренные и оцененные фильмы
на 80% проходит обучение на 20% тестирование
потом на вход к системе идут все непросмотренные фильмы и сортируются от наибольшей совместимости к наименьшей
каждые 5(10) оценок система перезапускается и переобучает ии, обновляя рейтинг подходящих фильмов
*/

class TemperamentDeterminant
{
public:
	enum GenreTypes
	{
		Fiction,
		Fantasy,
		Horror,
		Thriller,
		Mystic,
		ActionFilm,
		Drama,
		Detective,
		Adventures,
		Comedy,
		Documentary,
		Melodrama,
		Family,
		Cartoon,
		Historical,
		Military,
		Crime,
		Western,
		Biography,
		Sport,
		TVWebShow,
		Anime,
		Music,
		Musical,
	};
	struct Genre
	{
		GenreTypes genreTypes;
		float speed;
		float positivity;
	};
public:
	TemperamentDeterminant();
	void saveMoviesParametersToScv(const char* path);							// call after filling vector with addMovieParameters
	void addMovieParameters(std::vector<GenreTypes> genresVector, float mark);	// call for each single movie
	void clear();																// call after save. just clears vector after work

private:
	
	enum TemperamentTypes
	{
		Sanguine,
		Phlegmatic,
		Choleric,
		Melancholic,
	};
	struct Movie
	{
		float speed;
		float positivity;
		float mark;
	};
	std::vector<Movie> movies;
};