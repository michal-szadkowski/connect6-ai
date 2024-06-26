#include "Node.h"

#include <cmath>
#include <limits>
#include <memory>

Node::Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst) :
    parent(std::move(parent)), pos(pos), color(color), isFirstOfMove(isFirst)
{}

std::vector<std::shared_ptr<Node>> Node::Expand(const Board &currentBoard)
{
    if (expanded)
        return children;
    if (currentBoard.GetResult() != Color::None)
    {
        expanded = true;
        return children;
    }
    auto positions = currentBoard.GetAllEmpty();
    children.reserve(positions.size());
    Color nextColor = isFirstOfMove ? color : Reverse(color);
    for (auto p : positions)
    {
        children.emplace_back(std::make_shared<Node>(shared_from_this(), p, nextColor, !isFirstOfMove));
    }
    expanded = true;
    return children;
}


Board Node::GetResultingBoard(const Board &rootBoard) const
{
    Board b = rootBoard;
    if (auto p = parent.lock())
    {
        b = p->GetResultingBoard(b);
        if (pos != StonePos::Empty())
            b.PutStone(pos, color);
    }
    return b;
}

double Node::GetValue(double expRate) const
{
    if (visitCount == 0)
        return std::numeric_limits<double>::infinity();
    double result = score * 1.0 / visitCount;
    if (auto p = parent.lock())
    {
        result += expRate * std::sqrt(std::log(p->visitCount) / visitCount);
    }
    return result;
}
unsigned int Node::GetVisitCount() const { return visitCount; }
double Node::GetScore() const { return score * 1.0 / visitCount; }


int Node::PropagateResult(Color result)
{
    ++visitCount;
    if (color == result)
        ++score;
    else if (color == Reverse(result))
        --score;
    int depth = 0;
    if (auto p = parent.lock())
    {
        depth = p->PropagateResult(result);
    }
    return depth + 1;
}
