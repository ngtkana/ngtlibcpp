#!/bin/bash
Get-Content .\\library\\datasets_and_query\\disjoint_set.cpp  | while read line
do
  echo $line
done