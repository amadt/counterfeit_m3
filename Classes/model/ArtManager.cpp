#include "ArtManager.h"
#include <math.h>       /* floor */
#include "Types.h"

using namespace cocos2d;
extern float G_blobScale;

Art::Art(int id)
:id(id)
, croppedOffset(0)
{}

Gallary::Gallary(int id)
: id(id)
{}


// singleton stuff
static ArtManager *s_ArtManager = nullptr;

ArtManager* ArtManager::getInstance()
{
	if (!s_ArtManager)
	{
		s_ArtManager = new ArtManager();
	}

	return s_ArtManager;
}


ArtManager::ArtManager() 
{
	//create all the art
	/********************
	 * VAN GOGH 
	 ********************/
	{
		Art* art = new Art(1);
		art->name = "Starry Night";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/StarryNight.jpg";
		art->year = 1889;
		_art.push_back(art);
	}
	{
		Art* art = new Art(2);
		art->name = "Wheat Field With Cypresses";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/WheatFieldWithCypresses.jpg";
		art->year = 1889;
		_art.push_back(art);
	}
	{
		Art* art = new Art(3);
		art->name = "Self Portrait";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/SelfPortrait.jpg";
		art->croppedOffset = 100;
		art->year = 1889;
		_art.push_back(art);
	}
	{
		Art* art = new Art(4);
		art->name = "Cafe Terrace at Night";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/CafeTerraceAtNight.jpg";
		art->year = 1888;
		_art.push_back(art);
	}
	{
		Art* art = new Art(5);
		art->name = "Irises";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/Irises.jpg";
		art->year = 1890;
		_art.push_back(art);
	}
	{
		Art* art = new Art(6);
		art->name = "The Potato Eaters";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/ThePotatoEaters.jpg";
		art->year = 1885;
		_art.push_back(art);
	}
	{
		Art* art = new Art(7);
		art->name = "Self Portrait with Pipe";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/SelfPortraitWithPipe.jpg";
		art->year = 1886;
		_art.push_back(art);
	}
	{
		Art* art = new Art(8);
		art->name = "Wheat Field with Crows";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/WheatFieldWithCrows.jpg";
		art->year = 1886;
		_art.push_back(art);
	}
	{
		Art* art = new Art(9);
		art->name = "Starry Night Over the Rhone";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/StarryNightOverTheRhone.jpg";
		art->year = 1890;
		_art.push_back(art);
	}
	{
		Art* art = new Art(10);
		art->name = "House In Auvers";
		art->artist = "Vincent Van Gogh";
		art->image = "Art/VanGogh/HousesInAuvers.jpg";
		art->year = 1890;
		_art.push_back(art);
	}

	/********************
	 * Seurat
	 ********************/

	{
		Art* art = new Art(11);
		art->name = "The Eiffel Tower";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_TheEiffelTower1889.jpg";
		art->year = 1889;
		_art.push_back(art);
	}
	{
		Art* art = new Art(12);
		art->name = "Le Chahut Invitations";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/LeChahutInvitation1889.jpg";
		art->year = 1889;
		art->croppedOffset = 150;
		_art.push_back(art);
	}
	{
		Art* art = new Art(13);
		art->name = "A Sunday Afternoon on the Island of La Grande Jatte";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_ASundayAfternoon.jpg";
		art->year = 1884;
		_art.push_back(art);
	}
	{
		Art* art = new Art(14);
		art->name = "Circus Sideshow";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_CircusSideshow1887.jpg";
		art->year = 1887;
		_art.push_back(art);
	}
	
	{
		Art* art = new Art(15);
		art->name = "Banks of Seine";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/BanksOfSeine1888.jpg";
		art->year = 1888;
		art->croppedOffset = 50;
		_art.push_back(art);
	}
	{
		Art* art = new Art(16);
		art->name = "The Circus";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/TheCircus1891.jpg";
		art->year = 1904;
		_art.push_back(art);
	}
	{
		Art* art = new Art(17);
		art->name = "Bathing At Asnieres";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_BathingAtAsnieres1884.jpg";
		art->year = 1885;
		_art.push_back(art);
	}
	{
		Art* art = new Art(18);
		art->name = "La Grande Jatte";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_LaGrandeJatte1884.jpg";
		art->year = 1884;
		art->croppedOffset = 50;
		_art.push_back(art);
	}
	{
		Art* art = new Art(19);
		art->name = "Young Woman Powdering Herself";
		art->artist = "Georges Lemmen";
		art->image = "Art/Seurat/Seurat_YoungWomanPowderingHerself1890.jpg";
		art->year = 1890;
		art->croppedOffset = 90;
		_art.push_back(art);
	}
	{
		Art* art = new Art(20);
		art->name = "Alfalfa, St. Denis";
		art->artist = "Georges Seurat";
		art->image = "Art/Seurat/Seurat_AlfalfaStDenis1886.jpg";
		art->year = 1886;
		_art.push_back(art);
	}

	/********************
	 * MONET
	 ********************/

	{
		Art* art = new Art(21);
		art->name = "Water Lilies";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_WaterLilies1919.jpg";
		art->year = 1919;
		_art.push_back(art);
	}
	{
		Art* art = new Art(22);
		art->name = "Woman with a Parasol";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_WomanParasol.jpg";
		art->year = 1875;
		art->croppedOffset = 200;
		_art.push_back(art);
	}
	{
		Art* art = new Art(23);
		art->name = "The Manneport, Rock Arch West of Etretat";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_RockArchWestOfEtretat.jpg";
		art->year = 1883;
		_art.push_back(art);
	}
	{
		Art* art = new Art(24);
		art->name = "Bridge Over a Pond of Water Lilies";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_BridgeOverPond.jpg";
		art->year = 1899;
		art->croppedOffset = 40;
		_art.push_back(art);
	}
	{
		Art* art = new Art(25);
		art->name = "Palazzo da Mula in Venice";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_PalaceFromMulaVenice.jpg";
		art->year = 1908;
		art->croppedOffset = 25;
		_art.push_back(art);
	}
	{
		Art* art = new Art(26);
		art->name = "Railway Bridge at Argenteuil";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_RailwayBridgeAtArgenteuil1873.jpg";
		art->year = 1873;
		_art.push_back(art);
	}
	{
		Art* art = new Art(27);
		art->name = "Self Portrait With A Beret";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_SelfPortraitWithBeret1886.jpg";
		art->year = 1886;
		_art.push_back(art);
	}
	{
		Art* art = new Art(28);
		art->name = "Impression Sunrise";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_ImpressionSunrise.jpg";
		art->year = 1872;
		_art.push_back(art);
	}
	{
		Art* art = new Art(29);
		art->name = "Rouen Cathedral";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_RouenCathedral.jpg";
		art->year = 1893;
		_art.push_back(art);
	}
	{
		Art* art = new Art(30);
		art->name = "Haystacks, Sun in the Mist";
		art->artist = "Claude Monet";
		art->image = "Art/Monet/Monet_HaystacksSunInTheMist.jpg";
		art->year = 1919;
		_art.push_back(art);
	}

	/********************
	* Klimt
	********************/

	{
		Art* art = new Art(31);
		art->name = "The Kiss";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_TheKiss1908.jpg";
		art->year = 1908;
		art->croppedOffset = 160;
		_art.push_back(art);
	}
	{
		Art* art = new Art(32);
		art->name = "Country Garden with Sunflowers";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_CountryGardenWithSunflowers1906.jpg";
		art->year = 1906;
		_art.push_back(art);
	}
	{
		Art* art = new Art(33);
		art->name = "Malcesine on Lake Garda";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_MalcesineOnLakeGarda.jpg";
		art->year = 1913;
		_art.push_back(art);
	}
	{
		Art* art = new Art(34);
		art->name = "The Tree of Life, Stoclet Frieze";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_TheTreeOfLifeStocletFrieze.jpg";
		art->year = 1905;
		_art.push_back(art);
	}
	{
		Art* art = new Art(35);
		art->name = "Portrait of Adele Bloch Bauer";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_PortraitOfAdeleBlochBauer.jpg";
		art->year = 1907;
		art->croppedOffset = 140;
		_art.push_back(art);
	}
	{
		Art* art = new Art(36);
		art->name = "Cartoon for the Frieze of the Villa Stoclet";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_CartoonForTheFriezeOfTheVillaStoclet.jpg";
		art->year = 1909;
		_art.push_back(art);
	}
	{
		Art* art = new Art(37);
		art->name = "Lady With Fan";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_LadyWithFan1918.jpg";
		art->year = 1918;
		art->croppedOffset = 140;
		_art.push_back(art);
	}
	{
		Art* art = new Art(38);
		art->name = "Flower Garden";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_FlowerGarden1907.jpg";
		art->year = 1907;
		_art.push_back(art);
	}
	{
		Art* art = new Art(39);
		art->name = "Music";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_Music1895.jpg";
		art->year = 1895;
		art->croppedOffset = 60;
		_art.push_back(art);
	}
	{
		Art* art = new Art(40);
		art->name = "Expectation";
		art->artist = "Gustav Klimt";
		art->image = "Art/Klimt/Kilmt_Expectation1909.jpg";
		art->year = 1909;
		art->croppedOffset = 170;
		_art.push_back(art);
	}

	/********************
	* Mucha
	********************/

	{
		Art* art = new Art(41);
		art->name = "Biscuits Lefevre Utile";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/AlphonseMucha_BiscuitsLefevreUtile1896.jpg";
		art->year = 1896;
		art->croppedOffset = 180;
		_art.push_back(art);
	}
	{
		Art* art = new Art(42);
		art->name = "Zodiac";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/AlphonseMucha_Zodiac.jpg";
		art->year = 1896;
		art->croppedOffset = 100;
		_art.push_back(art);
	}
	{
		Art* art = new Art(43);
		art->name = "Dance";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_Dance1898.jpg";
		art->year = 1898;
		art->croppedOffset = 175;
		_art.push_back(art);
	}
	{
		Art* art = new Art(44);
		art->name = "Cycles Perfecta";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/AlphonseMucha_CyclesPerfecta1902.jpg";
		art->year = 1902;
		_art.push_back(art);
	}
	{
		Art* art = new Art(45);
		art->name = "Job";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_Job1896.jpg";
		art->croppedOffset = 100;
		art->year = 1896;
		_art.push_back(art);
	}
	{
		Art* art = new Art(46);
		art->name = "Sarah Bernhardt";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_SarahBernhardt1896.jpg";
		art->year = 1902;
		art->croppedOffset = 115;
		_art.push_back(art);
	}
	{
		Art* art = new Art(47);
		art->name = "Spring";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_Spring1896.jpg";
		art->year = 1896;
		art->croppedOffset = 170;
		_art.push_back(art);
	}
	{
		Art* art = new Art(48);
		art->name = "Lance Parfum Rodo";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_LanceParfumRodo1896.jpg";
		art->year = 1896;
		art->croppedOffset = 60;
		_art.push_back(art);
	}
	{
		Art* art = new Art(49);
		art->name = "Bieres de la Muse";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_BieresDeLaMuse.jpg";
		art->year = 1897;
		art->croppedOffset = 40;
		_art.push_back(art);
	}
	{
		Art* art = new Art(50);
		art->name = "Monaco Monte Carlo";
		art->artist = "Alphonse Mucha";
		art->image = "Art/Mucha/Mucha_MonacoMonteCarlo1897.jpg";
		art->year = 1897;
		art->croppedOffset = 75;
		_art.push_back(art);
	}


	/********************
	* Paul Signac
	********************/

	{
		Art* art = new Art(51);
		art->name = "Portrait of Felix Feneon";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/Signac_PortraitOfFelixFeneon1890.jpg";
		art->year = 1890;
		art->croppedOffset = 60;
		_art.push_back(art);
	}
	{
		Art* art = new Art(52);
		art->name = "The Yellow Sail, Venice";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/Signac_YellowSail.jpg";
		art->year = 1904;
		_art.push_back(art);
	}
	{
		Art* art = new Art(53);
		art->name = "The Dining Room";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/Signac_Breakfast1886.jpg";
		art->year = 1886;
		_art.push_back(art);
	}
	{
		Art* art = new Art(54);
		art->name = "The Port of Saint-Tropez";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/ThePortOfSaintTropez1901.jpg";
		art->year = 1901;
		art->croppedOffset = 60;
		_art.push_back(art);
	}
	{
		Art* art = new Art(55);
		art->name = "Capo di Noli";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/CapoDiNoli1898.jpg";
		art->year = 1898;
		_art.push_back(art);
	}
	{
		Art* art = new Art(56);
		art->name = "Grand Canal (Venice)";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/GrandCanal1905.jpg";
		art->year = 1905;
		_art.push_back(art);
	}
	{
		Art* art = new Art(57);
		art->name = "Sunday";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/Signac_Sunday1890.jpg";
		art->year = 1890;
		art->croppedOffset = 40;
		_art.push_back(art);
	}
	{
		Art* art = new Art(58);
		art->name = "The Demolisher";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/Signac_TheDemolisher1899.jpg";
		art->year = 1889;
		art->croppedOffset = 120;
		_art.push_back(art);
	}
	{
		Art* art = new Art(59);
		art->name = "The Palpal Palace, Avignon";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/ThePapalPalaceAvignon1909.jpg";
		art->year = 1909;
		_art.push_back(art);
	}
	{
		Art* art = new Art(60);
		art->name = "Women at the Well";
		art->artist = "Paul Signac";
		art->image = "Art/Signac/WomenAtTheWell1892.jpg";
		art->year = 1892;
		art->croppedOffset = 30;
		_art.push_back(art);
	}

	/********************
	* Rembrant
	********************/

	{
		Art* art = new Art(61);
		art->name = "The Nightwatch";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheNightwatch1642.jpg";
		art->year = 1642;
		_art.push_back(art);
	}
	{
		Art* art = new Art(61);
		art->name = "Christ in the Storm";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/ChristInTheStorm1633.jpg";
		art->year = 1633;
		_art.push_back(art);
	}
	{
		Art* art = new Art(62);
		art->name = "Syndics of the Drapers' Guild";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/SyndicsOfTheDrapers'Guild1662.jpg";
		art->year = 1662;
		_art.push_back(art);
	}
	{
		Art* art = new Art(63);
		art->name = "Flora";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/Flora1634.jpg";
		art->year = 1634;
		art->croppedOffset = 80;
		_art.push_back(art);
	}
	{
		Art* art = new Art(64);
		art->name = "Belshazzar's Feast";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/Belshazzar'sFeast1635.jpg";
		art->year = 1635;
		art->croppedOffset = 50;
		_art.push_back(art);
	}
	{
		Art* art = new Art(65);
		art->name = "The Artist in His Studio";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheArtistInHisStudio1628.jpg";
		art->year = 1628;
		_art.push_back(art);
	}
	{
		Art* art = new Art(66);
		art->name = "Self Portrait with Beret";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/SelfPortraitWithBeretAndTurnedUpCollar1659.jpg";
		art->croppedOffset = 100;
		art->year = 1659;
		_art.push_back(art);
	}
	{
		Art* art = new Art(67);
		art->name = "The Return of the Prodigal Son";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheReturnOfTheProdigalSon1669.jpg";
		art->year = 1669;
		art->croppedOffset = 20;
		_art.push_back(art);
	}
	{
		Art* art = new Art(68);
		art->name = "The Anatomy Lesson of Dr Nicolaes Tulp";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheAnatomyLessonOfDrNicolaesTulp1632.jpg";
		art->year = 1632;
		_art.push_back(art);
	}
	{
		Art* art = new Art(69);
		art->name = "The Holy Family";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheHolyFamily1645.jpg";
		art->year = 1645;
		art->croppedOffset = -50;
		_art.push_back(art);
	}
	{
		Art* art = new Art(70);
		art->name = "The Conspiracy of Claudius Civilis";
		art->artist = "Rembrandt";
		art->image = "Art/Rembrant/TheConspiracyOfClaudiusCivilis1662.jpg";
		art->year = 1662;
		_art.push_back(art);
	}

	/********************
	* Kandinsky
	********************/

	{
		Art* art = new Art(71);
		art->name = "Composition VI";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/compositionVI1913.jpg";
		art->year = 1913;
		_art.push_back(art);
	}
	{
		Art* art = new Art(72);
		art->name = "Moscow I";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/moscowI1916.jpg";
		art->year = 1916;
		_art.push_back(art);
	}
	{
		Art* art = new Art(73);
		art->name = "Murnau Dorfstrasse";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/MurnauDorfstrasse1908.jpg";
		art->year = 1908;
		_art.push_back(art);
	}
	{
		Art* art = new Art(74);
		art->name = "Color Study Squares with Concentric Circles";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/colorStudySquaresWithConcentricCircles1913.jpg";
		art->year = 1913;
		_art.push_back(art);
	}
	{
		Art* art = new Art(75);
		art->name = "Composition IV";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/CompositionIV1911.jpg";
		art->year = 1911;
		_art.push_back(art);
	}
	{
		Art* art = new Art(76);
		art->name = "Blue Segment";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/BlueSegment1921.jpg";
		art->year = 1921;
		_art.push_back(art);
	}
	{
		Art* art = new Art(77);
		art->name = "CompositionVII";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/CompositionVII1913.jpg";
		art->year = 1913;
		_art.push_back(art);
	}
	{
		Art* art = new Art(78);
		art->name = "Improvisation 26";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/Improvisation261912.jpg";
		art->year = 1912;
		_art.push_back(art);
	}
	{
		Art* art = new Art(79);
		art->name = "BlackSpot";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/BlackSpot1912.jpg";
		art->year = 1912;
		_art.push_back(art);
	}
	{
		Art* art = new Art(80);
		art->name = "Murnau Garden II";
		art->artist = "Wassily Kandinsky";
		art->image = "Art/Kandinsky/MurnauGardenII1910.jpg";
		art->year = 1910;
		_art.push_back(art);
	}

	/********************
	* Renoir
	********************/

	{
		Art* art = new Art(81);
		art->name = "A Girl with a Watering Can";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/AGirlWithAWateringCan1876.jpg";
		art->year = 1876;
		art->croppedOffset = 130;
		_art.push_back(art);
	}
	{
		Art* art = new Art(82);
		art->name = "Dance at le Moulin de la Galette";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/DanceAtLeMoulinDeLaGalette1876.jpg";
		art->year = 1876;
		_art.push_back(art);
	}
	{
		Art* art = new Art(83);
		art->name = "By The Seashore";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/ByTheSeashore1883.jpg";
		art->year = 1883;
		art->croppedOffset = 15;
		_art.push_back(art);
	}
	{
		Art* art = new Art(84);
		art->name = "The Theater Box";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/TheTheaterBox1874.jpg";
		art->year = 1874;
		art->croppedOffset = 180;
		_art.push_back(art);
	}
	{
		Art* art = new Art(85);
		art->name = "The Spring";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/TheSring1876.jpg";
		art->year = 1876;
		art->croppedOffset = 160;
		_art.push_back(art);
	}
	{
		Art* art = new Art(86);
		art->name = "Two Sisters";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/TwoSisters1881.jpg";
		art->year = 1881;
		art->croppedOffset = 20;
		_art.push_back(art);
	}
	{
		Art* art = new Art(87);
		art->name = "Luncheon of the Boating Party";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/LuncheonOfTheBoatingParty1881.jpg";
		art->year = 1881;
		_art.push_back(art);
	}
	{
		Art* art = new Art(88);
		art->name = "By the Water";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/ByTheWater1880.jpg";
		art->year = 1880;
		_art.push_back(art);
	}
	{
		Art* art = new Art(89);
		art->name = "Girls at the Piano";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/GirlsAtThePiano1892.jpg";
		art->year = 1892;
		art->croppedOffset = 50;
		_art.push_back(art);
	}
	{
		Art* art = new Art(90);
		art->name = "Self Portrait";
		art->artist = "Pierre-Auguste Renoir";
		art->image = "Art/Renoir/SelfPortrait1875.jpg";
		art->year = 1875;
		_art.push_back(art);
	}

	/********************
	* Vermeer
	********************/

	{
		Art* art = new Art(91);
		art->name = "Girl with a Pearl Earring";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/GirlWithAPearlEarring1665.jpg";
		art->year = 1665;
		_art.push_back(art);
	}
	{
		Art* art = new Art(92);
		art->name = "The Geographer";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheGeographer1669.jpg";
		art->year = 1669;
		_art.push_back(art);
	}
	{
		Art* art = new Art(93);
		art->name = "The Music Lesson";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheMusicLesson1665.jpg";
		art->year = 1665;
		art->croppedOffset = 30;
		_art.push_back(art);
	}
	{
		Art* art = new Art(94);
		art->name = "The Astronomer";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheAstronomer1668.jpg";
		art->year = 1668;
		_art.push_back(art);
	}
	{
		Art* art = new Art(95);
		art->name = "View of Delft";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/ViewOfDelft1661.jpg";
		art->year = 1661;
		art->croppedOffset = -40;
		_art.push_back(art);
	}
	{
		Art* art = new Art(96);
		art->name = "The Milkmaid";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheMilkmaid1658.jpg";
		art->year = 1658;
		art->croppedOffset = 80;
		_art.push_back(art);
	}
	{
		Art* art = new Art(97);
		art->name = "The Concert";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheConcert1664.jpg";
		art->year = 1664;
		_art.push_back(art);
	}
	{
		Art* art = new Art(98);
		art->name = "The Procuress";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheProcuress1656.jpg";
		art->year = 1656;
		art->croppedOffset = 150;
		_art.push_back(art);
	}
	{
		Art* art = new Art(99);
		art->name = "The Girl with the Wine Glass";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheGirlWithTheWineGlass1659.jpg";
		art->year = 1659;
		art->croppedOffset = 20;
		_art.push_back(art);
	}
	{
		Art* art = new Art(100);
		art->name = "The Art of Painting";
		art->artist = "Johannes Vermeer";
		art->image = "Art/Vermeer/TheArtOfPainting1860.jpg";
		art->year = 1860;
		_art.push_back(art);
	}

	/********************
	* Da Vinci
	********************/

	{
		Art* art = new Art(101);
		art->name = "Mona Lisa";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/MonaLisa1513.jpg";
		art->year = 1513;
		art->croppedOffset = 145;
		_art.push_back(art);
	}
	{
		Art* art = new Art(102);
		art->name = "The Virgin and Child With St Anne";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/TheVirginAndChildWithStAnne1513.jpg";
		art->year = 1513;
		art->croppedOffset = 40;
		_art.push_back(art);
	}
	{
		Art* art = new Art(103);
		art->name = "The Last Supper";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/TheLastSupper1495.jpg";
		art->year = 1495;
		_art.push_back(art);
	}
	{
		Art* art = new Art(104);
		art->name = "Virgin of the Rocks";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/VirginOfTheRocks1484.jpg";
		art->croppedOffset = -20;
		art->year = 1484;
		_art.push_back(art);
	}
	{
		Art* art = new Art(105);
		art->name = "The Lady with the Ermine Cecilia Gallerani";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/TheLadyWithTheErmineCeciliaGallerani1496.jpg";
		art->year = 1496;
		art->croppedOffset = 110;
		_art.push_back(art);
	}
	{
		Art* art = new Art(106);
		art->name = "Adoration of the Magi";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/AdorationOfTheMagi1481.jpg";
		art->year = 1481;
		_art.push_back(art);
	}
	{
		Art* art = new Art(107);
		art->name = "A Belle Ferronniere";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/ABelleFerronniere1496.jpg";
		art->year = 1496;
		art->croppedOffset = 100;
		_art.push_back(art);
	}
	{
		Art* art = new Art(108);
		art->name = "The Virgin and Child with St Anne and John the Baptist";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/TheVirginAndChildWithStAnneAndJohnTheBaptist1500.jpg";
		art->year = 1500;
		art->croppedOffset = 220;
		_art.push_back(art);
	}
	{
		Art* art = new Art(109);
		art->name = "The Annuciation";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/TheAnnuciation1473.jpg";
		art->year = 1473;
		_art.push_back(art);
	}
	{
		Art* art = new Art(110);
		art->name = "Head of a Woman";
		art->artist = "Leonardo da Vinci";
		art->image = "Art/DaVinci/HeadOfAWoman1508.jpg";
		art->year = 1508;
		_art.push_back(art);
	}


	/********************************************************
	 ********************************************************
	           GALLARIES
	 ********************************************************
	 ********************************************************/

	{
		Gallary* gallary = new Gallary(0);
		gallary->name = "Vincent Van Gogh";
		gallary->romanNumber = "I";
		gallary->image = "Art/VanGogh/SelfPortrait.jpg";
		for(int i = 1; i <= 10; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(1);
		gallary->name = "Georges Seurat";
		gallary->romanNumber = "II";
		gallary->image = "Art/Seurat/Seurat_ASundayAfternoon.jpg";
		for (int i = 11; i <= 20; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(2);
		gallary->name = "Da Vinci";
		gallary->romanNumber = "III";
		gallary->image = "Art/DaVinci/MonaLisa1513.jpg";
		for (int i = 101; i <= 110; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(3);
		gallary->name = "Claude Monet";
		gallary->romanNumber = "IV";
		gallary->image = "Art/Monet/Monet_SelfPortraitWithBeret1886.jpg";
		for (int i = 21; i <= 30; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(4);
		gallary->name = "Alphonse Mucha";
		gallary->romanNumber = "V";
		gallary->image = "Art/Mucha/AlphonseMucha_CyclesPerfecta1902.jpg";
		for (int i = 41; i <= 50; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(5);
		gallary->name = "Renoir";
		gallary->romanNumber = "VI";
		gallary->image = "Art/Renoir/SelfPortrait1875.jpg";
		for (int i = 81; i <= 90; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(6);
		gallary->name = "Kandinsky";
		gallary->romanNumber = "VII";
		gallary->image = "Art/Kandinsky/CompositionVII1913.jpg";
		for (int i = 71; i <= 80; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(7);
		gallary->name = "Gustav Klimt";
		gallary->romanNumber = "VIII";
		gallary->image = "Art/Klimt/Kilmt_TheKiss1908.jpg";
		for (int i = 31; i <= 40; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(8);
		gallary->name = "Vermeer";
		gallary->romanNumber = "IX";
		gallary->image = "Art/Vermeer/GirlWithAPearlEarring1665.jpg";
		for (int i = 91; i <= 100; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(9);
		gallary->name = "Rembrant";
		gallary->romanNumber = "X";
		gallary->image = "Art/Rembrant/SelfPortraitWithBeretAndTurnedUpCollar1659.jpg";
		for (int i = 61; i <= 70; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	{
		Gallary* gallary = new Gallary(10);
		gallary->name = "Paul Signac";
		gallary->romanNumber = "XI";
		gallary->image = "Art/Signac/Signac_PortraitOfFelixFeneon1890.jpg";
		for (int i = 51; i <= 60; i++) gallary->artIds.push_back(i);
		_gallaries.push_back(gallary);
	}
	
}

Art* ArtManager::getArt(int id)
{
	for (Art* art : _art)  if (art->id == id) return art;
	return nullptr;
}

Gallary* ArtManager::getGallary(int id)
{
	for (Gallary* gallary : _gallaries)  if (gallary->id == id) return gallary;
	return nullptr;
}

