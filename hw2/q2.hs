class ShapeOps s where
  area :: s -> Double
  perimeter :: s -> Double

data Circle = Circle Double

instance ShapeOps Circle where
  area (Circle r) = pi * r * r
  perimeter (Circle r) = 2 * pi * r

data Rectangle = Rectangle Double Double

instance ShapeOps Rectangle where
  area (Rectangle w h) = w * h
  perimeter (Rectangle w h) = 2 * (w + h)

main :: IO ()
main = do
  print (area (Circle 5))
  print (perimeter (Circle 5))
  print (area (Rectangle 4 3))
  print (perimeter (Rectangle 4 3))
