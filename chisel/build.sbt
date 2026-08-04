ThisBuild / scalaVersion := "2.13.12"

val chiselVersion  = "6.6.0"
val testVersion    = "6.0.0"          // <-- chiseltest para Chisel 6

libraryDependencies ++= Seq(
  "org.chipsalliance" %% "chisel"     % chiselVersion,
  "edu.berkeley.cs"   %% "chiseltest" % testVersion % Test,
  "org.scalatest"     %% "scalatest"  % "3.2.17"    % Test
)

//libraryDependencies += "org.chipsalliance" %% "rocket-chip-blocks" % "1.0.0" 

// plugin V6: artefato inclui o patch da Scala => CrossVersion.full
addCompilerPlugin(
  "org.chipsalliance" % "chisel-plugin" % chiselVersion cross CrossVersion.full
)



