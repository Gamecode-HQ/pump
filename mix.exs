defmodule Pump.MixProject do
  use Mix.Project

  def project do
    [
      app: :pump,
      version: "1.0.1",
      elixir: "~> 1.6",
      start_permanent: Mix.env() == :prod,
      deps: deps(),
      compilers: [:elixir_make | Mix.compilers()],
      make_clean: ["clean"],
    ]
  end

  def application do
    [
      mod: {Pump.Application, []},
      extra_applications: [:logger, :os_mon]
    ]
  end

  defp deps do
    [
      {:elixir_make, "~> 0.4", runtime: false},
      {:jason, "~> 1.0"}, {:tesla, "1.0.0"}
    ]
  end
end
