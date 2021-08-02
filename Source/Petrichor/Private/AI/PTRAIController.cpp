// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "AI/PTRAIController.h"


APTRAIController::APTRAIController( const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsPlayerState = true;
}
