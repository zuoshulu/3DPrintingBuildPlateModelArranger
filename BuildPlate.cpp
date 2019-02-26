#include <iostream>
#include <vector>
#include <deque>
#include "BuildPlate.h"
using namespace std;

// class template function to take any type container as input parameter
template <class M>
bool BuildPlate::arrangeModel(M models)
{
	if (models.size() == 0)
		return false;

	int maxX = 0;
	int maxY = 0;
	for (Model &m : models)
	{
		if (placing(m))
		{
			printf("Packed %d x %d rectangle at location (%d,%d)\n", m.getLength(), m.getWidth(), m.getX(), m.getY());
			maxX = max(maxX, m.getX() + m.getLength());
			maxY = max(maxY, m.getY() + m.getWidth());
		}
		else
		{
			cout << "Failed to fit a model with size " << m.getLength() << " x " << m.getWidth() << endl;
			return false;
		}
	}
	// Center the models from bottom left to center for better printing quality
	int xOffset = (length - maxY) / 2; // Calculate the model region distance to the center at X-axis
	int yOffset = (width - maxX) / 2;  // Calculate the model region distance to the center at Y-axis
	cout << "Move models from left to right on X-axis(+" << xOffset << "), and move up on Y-Axis(+" << yOffset << ")\n";

	// Map model position to a build plate with center at (0, 0)
	for (Model &m : models)
	{
		m.setX(m.getX() + xOffset - length / 2);
		m.setY(m.getY() + yOffset - width / 2);
		printf("Moved %d x %d rectangle at location (%d,%d)\n", m.getLength(), m.getWidth(), m.getX(), m.getY());
	}
	return true;
}
template bool BuildPlate::arrangeModel<vector<Model>>(vector<Model>);
template bool BuildPlate::arrangeModel<deque<Model>>(deque<Model>);

// Soloving 2D bin packing problem with Shelf's next fit algorithm
// Packing model rectangles from bottom left at position (0, 0)
// Time O(n), Space O(1)
bool BuildPlate::placing(Model &model)
{
	int modelLength = model.getLength();
	int modelWidth = model.getWidth();
	// Flip the model if it does not fit the current shelf
	if ((modelLength > modelWidth && modelWidth < shelfWidth) || // Filp if shelf width is bigger than model length
		(modelLength < modelWidth && modelWidth > shelfWidth)) // Filp if shelf width is smaller than model width
	{
		model.setFlipFlag(true);
		swap(modelLength, modelWidth);
	}
	else
		model.setFlipFlag(false);

	// Start a new shelf on top of the current shelf
	if (x + modelLength > length)
	{
		x = 0;
		y += shelfWidth;
		shelfWidth = 0;

		// Flip the long edge of rectangle to reduce new shelf width
		if (modelLength < modelWidth)
		{
			swap(modelLength, modelWidth);
			model.setFlipFlag(!model.getFlipFlag());
		}
	}

	// If the model does not fit in this oritentation, then flip it
	if (modelLength > length || y + modelWidth > width)
	{
		swap(modelLength, modelWidth);
		model.setFlipFlag(!model.getFlipFlag());
	}

	// If the previous filp still does not help, then it can not be fitted
	if (modelLength > length || y + modelWidth > width)
		return false;

	// Update the model location
	model.setLength(modelLength);
	model.setWitdh(modelWidth);
	model.setX(x);
	model.setY(y);

	x += modelLength; // Update current x to fit next model
	shelfWidth = max(shelfWidth, modelWidth);
	return true;
}
