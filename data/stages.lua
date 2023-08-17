-- Minlevel and multiplier are MANDATORY
-- Maxlevel is OPTIONAL, but is considered infinite by default
-- Create a stage with minlevel 1 and no maxlevel to disable stages
experienceStages = {
	{
		minlevel = 1,
		maxlevel = 1300,
		multiplier = 50000
	},
	{
		minlevel = 150,
		multiplier = 3
	}
}

skillsStages = {
	{
		minlevel = 10,
		maxlevel = 100,
		multiplier = 1100
	}, {
		minlevel = 61,
		maxlevel = 80,
		multiplier = 8
	}, {
		minlevel = 81,
		maxlevel = 110,
		multiplier = 5
	}, {
		minlevel = 111,
		maxlevel = 125,
		multiplier = 3
	}, {
		minlevel = 126,
		multiplier = 2
	}
}

magicLevelStages = {
	{
		minlevel = 0,
		maxlevel = 60,
		multiplier = 80
	}, {
		minlevel = 61,
		maxlevel = 80,
		multiplier = 5
	}, {
		minlevel = 81,
		maxlevel = 100,
		multiplier = 4
	}, {
		minlevel = 101,
		multiplier = 3
	}
}
