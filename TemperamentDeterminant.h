#pragma once

#include <vector>
#include <fstream>

/*
������� ������ ��������� 2 ����� ����� ���������� ����� ��� ������.
� csv ����, �� �������� ��, ���������� ����� ������:
	� - speed, positivity (0-1) (����� ������� ����� ���������� ������������ ���� 4 �������������)
	� - ������ ������ (0-1)
� ���� ���� ��� ������������� � ��������� ������
�� 80% �������� �������� �� 20% ������������
����� �� ���� � ������� ���� ��� ��������������� ������ � ����������� �� ���������� ������������� � ����������
������ 5(10) ������ ������� ��������������� � ����������� ��, �������� ������� ���������� �������
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